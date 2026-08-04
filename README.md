# 人脸检测小项目（C++）

项目配置骨架已就绪，检测代码由你自己编写。

## 已配置好的内容

- CMake 构建配置：自动查找本机 OpenCV（MinGW 4.1.0）
- 项目配置文件：`config.yaml`
- 目录：`src/`、`images/`、`outputs/`、`models/`

## 环境要求

- CMake 3.16 及以上
- MinGW-w64（g++）
- OpenCV 4.x（MinGW 构建版）

## 配置文件说明

`config.yaml` 使用 OpenCV `FileStorage` 支持的 YAML 格式，包含以下小节：

| 配置项 | 默认值 | 说明 |
| --- | --- | --- |
| `model.path` | 空 | 自定义级联模型路径 |
| `model.name` | `haarcascade_frontalface_default.xml` | 模型文件名 |
| `detect.scale_factor` | `1.1` | 每次扫描图像缩小的比例 |
| `detect.min_neighbors` | `5` | 候选框邻近矩形数 |
| `detect.min_size` | `[60, 60]` | 最小人脸尺寸 |
| `detect.max_size` | `[0, 0]` | 最大人脸尺寸，0 表示不限 |
| `draw.color` | `[0, 255, 0]` | 检测框颜色（BGR） |
| `draw.thickness` | `2` | 检测框线宽 |
| `io.input` | 空 | 默认输入图片路径，空则使用摄像头 |
| `io.camera_index` | `0` | 摄像头索引 |
| `io.output` | 空 | 结果保存路径，空则不保存 |
| `preprocess.resize_width` | `0` | 检测前缩放宽度，0 表示不缩放 |

## 编写代码后的构建

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

运行前把 OpenCV 的 DLL 加入 `PATH`：

```powershell
$env:Path = "E:\opencv\OpenCV-MinGW-Build-OpenCV-4.1.0-x64\x64\mingw\bin;$env:Path"
```

## 目录结构

```text
faceRecognition/
├── CMakeLists.txt     # CMake 构建配置
├── config.yaml        # 项目配置文件
├── src/               # 放你的 C++ 源码
├── images/            # 放待检测图片
├── outputs/           # 放检测结果图片
└── models/            # 放级联模型文件
```
