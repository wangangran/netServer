#include "LogFile.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

using namespace saran::base;

MMapFileWrite::MMapFileWrite(const std::string &basename, uint32_t memsize) :
    memSize_(memsize)
{
    fd_ = open(basename.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd_ < 0) {
        fprintf(stderr, "open file failed, errno = %d", errno);
    } else {
        ftruncate(fd_, memsize);    
        buffer_ = (char *)mmap(nullptr, memsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0);
        if (buffer_ == MAP_FAILED) {
            fprintf(stderr, "mmap file failed, errno = %d", errno);
        }
    }
}

MMapFileWrite::~MMapFileWrite()
{
    if (fd_ > 0) {
        close(fd_);
        fd_ = -1;
    }

    if (buffer_ != MAP_FAILED) {
        munmap(buffer_, memSize_);
    }
}

void MMapFileWrite::append(const char *msg, uint32_t len)
{
    if (len > memSize_ - writed_) {
        fprintf(stderr, "mmap memory overflow errno = %d", errno);
        return;
    }

    memcpy(buffer_ + writed_, msg, len);
    writed_ += len;
}

void MMapFileWrite::flush()
{
    if (buffer_ != MAP_FAILED) {
        msync(buffer_, memSize_, MS_ASYNC);
    }
}

uint32_t MMapFileWrite::wirttenBytes() const
{
    return writed_;
}

AppendFileWrite::AppendFileWrite(const std::string &filename) :
    fp_(fopen(filename.c_str(), "ae"))
{
    assert(fp_);
    setbuffer(fp_, buffer_, sizeof(buffer_));
}

AppendFileWrite::~AppendFileWrite()
{
    if (fp_) {
        fclose(fp_);
    }
}

void AppendFileWrite::append(const char *msg, uint32_t len)
{
    size_t written = 0;

    while (written != len) {
        size_t remain = len - written;
        size_t n = fwrite_unlocked(msg + n, sizeof(char), remain, fp_);
        if (n != remain) {
            int err = ferror(fp_);
            if (err) {
                fprintf(stderr, "AppendFileWrite::append failed %s\n", strerror(err));
                break;
            }
        }

        written += n;
    }

    writed_ += len;
}

void AppendFileWrite::flush()
{
    fflush(fp_);
}

uint32_t AppendFileWrite::wirttenBytes() const
{
    return writed_;
}

LogFile::LogFile(const std::string &basename, uint32_t rollSize, uint32_t flushInterval,
                 uint32_t checkInterval, FileWriterType fWriteType) :
    baseName_(basename),
    rollSize_(rollSize),
    flushInterval_(flushInterval),
    checkFreqCount_(checkInterval),
    fWriteType_(fWriteType)
{
    time_t now = 0;
    std::string filename = getLogFileName(baseName_, &now);
    if (fWriteType_ == MMAPFILE) {
        fileWrite_ = std::make_shared<MMapFileWrite>(filename, rollSize_);
    } else {
        fileWrite_ = std::make_shared<AppendFileWrite>(filename);
    }
}

void LogFile::append(const char *msg, uint32_t len)
{
    fileWrite_->append(msg, len);
    if (fileWrite_->wirttenBytes() > rollSize_) {
        rollFile();
    } else {
        ++count_;
        if (count_ >= checkFreqCount_) {
            count_ = 0;
            time_t now = time(nullptr);
            time_t thisPeriod = now / kRollPerSeconds_ * kRollPerSeconds_;
            if (thisPeriod != startOfPeriod_) {
                rollFile();
            } else if (now - lastFlush_ > flushInterval_){
                lastFlush_ = now;
                fileWrite_->flush();
            }
        }
    }
}

void LogFile::flush()
{
    fileWrite_->flush();
}

bool LogFile::rollFile()
{
time_t now = 0;
  std::string filename = getLogFileName(baseName_, &now);
  time_t start = now / kRollPerSeconds_ * kRollPerSeconds_;

  if (now > lastRoll_) {
    lastRoll_ = now;
    lastFlush_ = now;
    startOfPeriod_ = start;
    if (fWriteType_ == MMAPFILE) {
        fileWrite_ = std::make_shared<MMapFileWrite>(filename, rollSize_);
    } else {
        fileWrite_ = std::make_shared<AppendFileWrite>(filename);
    }
    return true;
  }
  return false;
}

std::string LogFile::getLogFileName(const std::string &basename, time_t *now)
{
    std::string filename;
    filename.reserve(basename.size() + 64);
    filename = basename;

    char timebuf[32];
    struct tm tm;
    *now = time(NULL);
    gmtime_r(now, &tm);
    strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S.", &tm);
    filename += timebuf;

    filename += getHostName();

    char pidBuf[32];
    snprintf(pidBuf, sizeof(pidBuf), ".%d", getpid());
    filename += pidBuf;

    filename += ".log";

    return filename;
}

std::string LogFile::getHostName()
{
    char hostName[256];
    if (0 == gethostname(hostName, sizeof(hostName))) {
        hostName[sizeof(hostName) - 1] = '\0';
        return hostName;
    } else {
        return "unknowhost";
    }
}

