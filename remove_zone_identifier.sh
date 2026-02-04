#!/bin/bash

# 删除 W3_report/Icraft文档转md 文件夹下所有的 Zone.Identifier 文件
TARGET_DIR="W3_report/Icraft文档转md"

if [ ! -d "$TARGET_DIR" ]; then
    echo "错误: 目录 $TARGET_DIR 不存在"
    exit 1
fi

echo "开始查找并删除 Zone.Identifier 文件..."
echo "目标目录: $TARGET_DIR"
echo ""

# 计数器
count=0

# 查找并删除所有 Zone.Identifier 文件
while IFS= read -r file; do
    echo "删除: $file"
    rm -f "$file"
    ((count++))
done < <(find "$TARGET_DIR" -name "*:Zone.Identifier" -o -name "*.Zone.Identifier")

echo ""
echo "完成! 共删除 $count 个文件"
