//
// Created by Administrator on 2024/3/7.
//

#include <iostream>
#include <vector>
#include "FileInfo.h"
#include <algorithm>

struct FileInfoCompare {
    bool smallFilePriority;

    FileInfoCompare() = default;

    bool operator()(const FileInfo* f1, const FileInfo* f2) const {
        return f1->recordInfo.fileSize >= f2->recordInfo.fileSize;
    }
};

class FileList {
public:
    void push(const FileInfo &info) {
        files_.push_back(new FileInfo(info));
    }

    void sort() {
        std::sort(files_.begin(), files_.end(), FileInfoCompare());
    }
private:
    std::vector<FileInfo*> files_;
};

int main(int argc, char **argv) {
    FileList fileList;
    FileInfo file;
    file.recordInfo.fileSize = 10485760;
    file.filePath = "/bwf_1.bwf";
    fileList.push(file);
    file.filePath = "/bwf_2.bwf";
    fileList.push(file);
    file.filePath = "/bwf_3.bwf";
    fileList.push(file);
    file.filePath = "/bz2_1.dps";
    fileList.push(file);
    file.filePath = "/bz2_2.dps";
    fileList.push(file);
    file.filePath = "/bz2_3.dps";
    fileList.push(file);
    file.filePath = "/docx_1.docx";
    fileList.push(file);
    file.filePath = "/docx_2.docx";
    fileList.push(file);
    file.filePath = "/docx_3.docx";
    fileList.push(file);
    file.filePath = "/doc_1.doc";
    fileList.push(file);
    file.filePath = "/doc_2.doc";
    fileList.push(file);
    file.filePath = "/doc_3.doc";
    fileList.push(file);
    file.filePath = "/dps_1.dps";
    fileList.push(file);
    file.filePath = "/dps_2.dps";
    fileList.push(file);
    file.filePath = "/dps_3.dps";
    fileList.push(file);
    file.filePath = "/et_1.et";
    fileList.push(file);
    file.filePath = "/et_2.et";
    fileList.push(file);
    file.filePath = "/et_3.et";
    fileList.push(file);

    fileList.sort();
    return 0;
}
