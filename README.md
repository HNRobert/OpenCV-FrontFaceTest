
<!--README.md-->
<!--OpenCV-FrontFaceTest-->
<!--Created by Robert He on 2024/10/13.-->

# macOS 下 C++ & OpenCV & Xcode 开发环境配置教程
<img width="2032" alt="image" src="https://github.com/user-attachments/assets/7b3595f1-0704-4dc5-aed5-4ac680bdefed">

本教程旨在帮助你在 macOS 上使用 Xcode 配置 C++ 和 OpenCV 开发环境，特别是对需要调用摄像头等权限的项目也有帮助。虽说简单，**但还是有一些可能会浪费你时间到小坑需要帮助你避开**。如果同为宁波诺丁汉大学的同学且需要安装 ```Homebrew```的话，建议到教学区连接 ```eduroam```网络，或者有条件的话使用魔法进行下载操作。

（他奶奶的，能自己上GitHub看到这里已经超越99%的同龄人了好吧，乐观一点☝️）

## 1. 安装 Homebrew

[Homebrew](https://brew.sh/) 是个好东西，它是 macOS 上的著名包管理工具，日后用 ```brew install ...``` 命令即可以轻松地在你的Mac上安装一些Windows等其他操作系统需要大费周章翻网页找资源的环境。类似于Ubuntu等Linux的 ```sudo apt install ...```。

打开终端并运行以下命令安装 Homebrew, 并添加到环境变量：

```zsh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
# 设置环境变量，保存并重新加载配置文件：
export PATH="/opt/homebrew/bin:$PATH"
source ~/.zshrc
# 如果你使用的是 bash，改为 "source ~/.bash_profile"， 其他以此类推
```

安装完成后，确保 brew 命令可以正常使用：

```zsh
brew --version
```

## 2. 安装 OpenCV

通过 Homebrew 安装 OpenCV：

```zsh
brew install opencv
```

简单吧？看看人家Windows上要怎么装怎么编译你就爽了😍

如果失败提示需要安装 Xcode Command Line Tool 之类的, 则需要先至 App Store 下载安装Xcode, 然后运行上面失败后提示的安装指令，再重新尝试 ```brew install opencv``` 即可

安装完成后，你可以使用以下命令来**验证 OpenCV 是否已成功安装**：

```zsh
brew list opencv
```

这将列出与 OpenCV 相关的文件和路径，Apple Silicon Based Mac 通常位于 /opt/homebrew/Cellar/opencv/ 目录下。**记住这些路径大概长什么样子，后面要考**。

目前一切正常的话效果如图：

<img width="697" alt="image" src="https://github.com/user-attachments/assets/f85a8d3c-163c-414f-a40d-51e626b003b5">

## 3. 在 Xcode 中配置 OpenCV

*好，这又是个大工程。但是我们不慌，教程就在这里👇*

### 3.1 创建新的 Xcode 项目

 1. 打开 Xcode（如果没下, 可在 ```App Store``` 里简单搜索下载安装），选择 ```Create a new Xcode project```。
 2. 选择 macOS 栏下 C++ 项目类型 (Command Line Tool)，点击 “Next”。
    
    <img width="1512" alt="image" src="https://github.com/user-attachments/assets/0474538a-8459-4984-84b6-9ea562774cf0">

 3. 为项目命名并选择存储位置，设置开发者\团队，其他选项随意，点击 “Create”。
    
    <img width="1512" alt="image" src="https://github.com/user-attachments/assets/5cc947fe-5c79-4a44-b541-fadb4986f4bb">

### 3.2 配置 OpenCV 库

1. 在 Xcode 中点击项目名称，选择左边 ```Targets``` 栏下目标。
2. 转到顶上 ```Build Settings``` 标签页。
3. 筛选名称, 在 ```Search Paths``` 部分找到 ```Header Search Paths```，**单击右侧空白**添加 OpenCV 的头文件路径 ( **可将4.10.0_11替换为你的版本号**，截止2024/10/14这是最新版本 )： ```/opt/homebrew/Cellar/opencv/4.10.0_11/include/opencv4```
   （如果是 **Intel Based Mac** 用户则可将其中的 ```/opt/homebrew``` 替换为 ```/local/usr```，**具体使用什么路径以上方 ```brew list opencv``` 显示结果为准， 下面所有类似路径同理**。）
4. 找到 ```Library Search Paths```，单击其右侧空白添加 OpenCV 库文件路径： ```/opt/homebrew/Cellar/opencv/4.10.0_11/lib```
   
   <img width="2032" alt="Screenshot 2024-10-14 at 03 12 24" src="https://github.com/user-attachments/assets/b2334403-9302-4b31-90cf-3819ba097cc7">

5. 筛选找到同目录下 ```Other Linker Flags```，单击其右侧的输入框粘贴入下面内容。（菜单界面单击粘贴进去即可，完成后可以双击进去验证是否分行）
   ```-lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_videoio```
   
   <img width="2032" alt="Screenshot 2024-10-14 at 03 19 46" src="https://github.com/user-attachments/assets/6d048944-5af2-4363-9f32-c9a7c37205f5">


   （这将自动帮你链接运行 OpenCV 程序所需的动态运行库，相当于 Win 中所需的的 .dll 文件）

### 3.3 测试 OpenCV 配置

在你的项目中，可以将下面这些```鲣殚```的 C++ 内容粘贴到 ```main.cpp``` 来测试 OpenCV 配置是否成功：

```C++
//
//  main.cpp
//  OpenCV-FrontFaceTest
//
//  Created by Robert He on 2024/9/26.
//

#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 加载一个效果不错的官方提供的预训练的人脸分类器
    // 按照实际文件位置修改
    String face_cascade_name = "/opt/homebrew/Cellar/opencv/4.10.0_11/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml";
    CascadeClassifier face_cascade;

    // 检查是否成功加载分类器
    if (!face_cascade.load(face_cascade_name)) {
        cout << "Error loading face cascade" << endl;
        return -1;
    }

    // 打开摄像头
    VideoCapture capture(0); // 0表示使用默认摄像头
    if (!capture.isOpened()) {
        cout << "Error opening video capture" << endl;
        return -1;
    }

    Mat frame;

    while (capture.read(frame)) {
        if (frame.empty()) {
            cout << "No captured frame -- Break!" << endl;
            break;
        }

        // 转为灰度图像（人脸检测通常在灰度图上效果更好）
        Mat frame_gray;
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray); // 均衡直方图以提高检测精度

        // 检测人脸
        std::vector<Rect> faces;
        face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        // 绘制矩形框在人脸周围
        for (size_t i = 0; i < faces.size(); i++) {
            // 使用 rectangle() 绘制矩形框
            rectangle(frame, faces[i], Scalar(255, 0, 255), 2);
        }
        
        // 显示结果
        imshow("Face Detection", frame);

        // 按下 'q' 键退出
        if (waitKey(10) == 'q') {
            break;
        }
    }

    return 0;
}

```

注意，运行本项目前，除了确认代码中**预训练模型模型地址正确**（实在找不到的话，本仓库中有，可以下载到你喜欢的地方后 command+option+c 复制路径，粘贴到项目中），还要在项目设置中选中 ```Targets``` 边栏目录下的项目、勾选 ```Signing & Capabilities``` 顶部栏下的 ```Disable Library Validation```项目来**允许第三方的lib被使用**，以及**开放在 ```Resource Access``` 下的 ```Camera``` 权限**（如下👇）。**macOS在安全上可从来不马虎**，但这对开发者还是会增加一点小小的门槛。

<img width="2032" alt="image" src="https://github.com/user-attachments/assets/3f72daad-2eb6-4f91-b4a0-e9e538470490">

一切就绪后按下 command+R 构建并运行项目。如果 Xcode 成功打开摄像头并在弹出窗口中能在识别的人脸周围画出矩形框，则说明 OpenCV 已正确配置。（窗口内按下q退出）

## 4. 常见问题排查

### 问题 1: opencv2/opencv.hpp 文件未找到

确保已正确配置 Header Search Paths。你可以通过 brew info opencv 命令确认 OpenCV 的安装路径是否准确。

### 问题 2: 构建失败，提示缺少动态库 (.dylib)

确保你在 “Other Linker Flags” 中正确添加了所需的 OpenCV 库 Flag。

## 结语

通过本教程，你已经成功在 macOS 上使用 Xcode 配置了 C++ 和 OpenCV 开发环境。你现在可以开始你的前脸检测项目或其他基于 OpenCV 的图像处理任务。

不过需要注意的是，该教程仅适合可以完全依赖 macOS 的同学进行 C++ & OpenCV 开发。建议各位同时学习Ubuntu与Windows的操作方案来锻炼自己的“配环境能力”

想要熟练掌握OpenCV还有很长的路要走，同学们继续努力吧 ☝️🤓
