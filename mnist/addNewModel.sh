#!/bin/bash

# Define MNIST_ML_ROOT as the current directory
MNIST_ML_ROOT=$(pwd)

# Check if MNIST_ML_ROOT is defined and not empty
if [[ -z $MNIST_ML_ROOT ]]; then
    echo "Please define MNIST_ML_ROOT"
    exit 1
fi

# Check if model name is provided as argument
if [[ -z $1 ]]; then
    echo "Please provide a model name"
    exit 1
fi

# Convert model name to lowercase
model_name_lower=$(echo "$1" | tr '[:upper:]' '[:lower:]')

# Create necessary directories and files
mkdir -p "$MNIST_ML_ROOT/$model_name_lower/include" "$MNIST_ML_ROOT/$model_name_lower/src"
touch "$MNIST_ML_ROOT/$model_name_lower/Makefile"
touch "$MNIST_ML_ROOT/$model_name_lower/include/${model_name_lower}.hpp"
touch "$MNIST_ML_ROOT/$model_name_lower/src/${model_name_lower}.cpp"

echo "Directories and files created successfully:"
echo "- $MNIST_ML_ROOT/$model_name_lower/include/${model_name_lower}.hpp"
echo "- $MNIST_ML_ROOT/$model_name_lower/src/${model_name_lower}.cpp"
