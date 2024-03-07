//
// Created by Administrator on 2023/9/27.
//

#ifndef FILESYNC_BASE_FILEINFO_H
#define FILESYNC_BASE_FILEINFO_H

#include <stdint.h>
#include <string>

struct RecordInfo {
    int id;                             // MySQL自增索引, 用于优化数据库查找效率（文件同步业务中用不到）
    uint64_t fileSize;                  // 文件大小
    uint64_t fileModTime;               // 文件最后修改时间
    bool isDir;                         // 是否为文件夹

    RecordInfo() {
        reset();
    }

    void reset() {
        id = 0;
        fileSize = 0;
        fileModTime = 0;
        isDir = false;
    }

    RecordInfo(const RecordInfo &lhs){
        *this = lhs;
    }

    bool operator==(const RecordInfo &lhs) const {
        return (this->fileSize == lhs.fileSize) &&
               (this->fileModTime == lhs.fileModTime) &&
               (this->isDir == lhs.isDir);
    }

    RecordInfo &operator=(const RecordInfo &lhs) {
        this->id = lhs.id;
        this->fileSize = lhs.fileSize;
        this->fileModTime = lhs.fileModTime;
        this->isDir = lhs.isDir;

        return *this;
    }
};

struct FileInfo {
    std::string filePath;               // 文件路径
    RecordInfo recordInfo;              // 文件记录信息

    FileInfo() {
        reset();
    }

    FileInfo(const FileInfo &lhs) {
        *this = lhs;
    }

    void reset() {
        filePath.clear();
        recordInfo.reset();
    }

    bool operator==(const FileInfo &lhs) {
        return (this->filePath == lhs.filePath) && (this->recordInfo == lhs.recordInfo);
    }

    FileInfo &operator=(const FileInfo &lhs) {
        this->filePath = lhs.filePath;
        this->recordInfo = lhs.recordInfo;

        return *this;
    }
};

#endif // FILESYNC_BASE_FILEINFO_H
