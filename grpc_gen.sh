#! /bin/bash

if [ $# -ne 2 ]; then
    echo "$0 proto_file_path output_dir"

    exit 1
fi

PROTO_FILE="$1"
OUTPUT_DIR="$2"

if [ ! -f "$PROTO_FILE" ]; then
    echo "没文件我生成个蛋"
    exit 1
fi

PROTO_DIR=$(dirname "$PROTO_FILE")
PROTO_NAME=$(basename "$PROTO_FILE")
GRPC_PLUGIN_ADDR=$(which grpc_cpp_plugin)

protoc --proto_path="$PROTO_DIR" --cpp_out="$OUTPUT_DIR" "$PROTO_NAME"
protoc --proto_path="$PROTO_DIR" --grpc_out="$OUTPUT_DIR" --plugin=protoc-gen-grpc="$GRPC_PLUGIN_ADDR" "$PROTO_NAME"