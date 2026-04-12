#import "../../template.typ": *

#show: project.with(
  title: "计算机网络 实验报告",
  author: "author",
  cover_info: (
    "课程名称": [计算机网络],
    "实验名称": [Webget & ByteStream],
    "姓名": [某某某],
    "学院": [计算机科学与技术学院],
    "系": [计算机科学与技术],
    "专业": [计算机科学与技术],
    "学号": [32xxxxxxxx],
    "指导教师": [某老师],
    "报告日期": [x 年 x 月 x 日],
  ),
)

= 浙江大学实验报告

== 实验目的

- 学习掌握 Linux 虚拟机的用法
- 学习掌握网页的抓取方法
- 学习掌握 ByteStream 的相关知识
- 学习掌握 C++ 的新特性

== 实验内容

- 安装配置 Linux 虚拟机并在其上完成本次实验。
- 编写小程序 `webget`，通过网络获取 web 页面，类似于 `wget`。
- 实现字节流 `ByteStream`：
  - 字节流可以从写入端写入，并以相同的顺序，从读取端读取；
  - 字节流是有限的，写者可以终止写入。而读者可以在读取到字节流末尾时，产生 `EOF` 标志，不再读取；
  - 支持流量控制，以控制内存的使用；
  - 写入的字节流可能会很长，必须考虑到字节流大于缓冲区大小的情况。

== 主要仪器设备

- 联网的 PC 机
- Linux 虚拟机

== 操作方法与实验步骤

- 鼓励参照 #link("https://xujinming1.github.io/2025netlab/", [2025 计算机网络实验文档]) 完成实验。

- 安装 #link("https://www.oracle.com/cn/virtualization/virtualbox/", [VirtualBox]) 及
  #link("https://stanford.edu/class/cs144/vm_files/cs144-fall-2025-x86.ova", [CS144 VirtualBox 虚拟机映像])。
  对于使用 ARM 芯片的 Mac 同学，可以使用 #link("https://mac.getutm.app/", [UTM 虚拟机]) 和对应 CS144 镜像
  #link("https://web.stanford.edu/class/cs144/vm_files/cs144-fall-2025-arm64.utm.tar.gz", [CS144 UTM 镜像])。

- 抓取网页：在正式进行编码工作之前，你需要对本实验第一个任务，即抓取一个网页，有更深刻的理解。
  - 在浏览器中，访问 http://cs144.keithw.org/hello 并观察结果。
  - 在你的虚拟中运行 `telnet cs144.keithw.org http` 命令，它告诉 telnet 程序在你的计算机与另一台计算机（名为 cs144.keithw.org）之间打开一个可靠的字节流，并在这台计算机运行一个特定的服务："http" 服务。
  - 输入 `GET /hello HTTP/1.1` 以及回车键，这告诉服务器 URL 的路径部分。
  - 输入 `Host: cs144.keithw.org` 以及回车键，这告诉服务器 URL 的主机部分。
  - 输入 `Connection: close` 以及回车键，这告诉服务器你已经完成了 HTTP 请求。
  - 再次输入回车发送请求。
  - 将返回结果与浏览器的返回结果进行比较。

- 准备工作：从 GitHub 上抓取初始代码文件并完成环境搭建。
  - 在你的虚拟机上，运行 `git clone https://github.com/sibo715/zju-comnet-labs.git` 命令来获取初始代码文件。
  - 运行 `cd sponge` 命令进入 sponge 目录。
  - 运行 `mkdir build` 命令构建 build 目录来编译实验代码。
  - 运行 `cd build` 命令进入 build 目录。
  - 运行 `cmake ..` 命令建立搭建系统。
  - 运行 `make` 命令编译源代码，需要注意每次你对项目进行了修改都需要运行 `make` 命令。
  - 实验代码的编写将以现代 C++ 风格完成，使用最新的特性尽可能安全地编程。

- 阅读 sponge 文档：sponge 封装了操作系统函数，请务必在编写实验代码前仔细阅读相关的基础代码文件。
  查阅 `libsponge/util` 目录：`file_descriptor.hh`, `socket.hh` 以及 `address.hh`。

- 实现 webget：完成 webget.cc 程序代码的编写以实现抓取网页的功能。
  - 从 build 目录下，在文本编辑器或 IDE 下打开 `../apps/webget.cc`。
  - 在 `get_URL` 函数中完成实现，实现代码使用 HTTP（Web）请求的格式。使用 `TCPSocket` 类以及 `Address` 类。
  - 运行 `make` 命令编译程序。
  - 运行 `./apps/webget cs144.keithw.org /hello` 命令进行程序的测试。
  - 通过上面的测试后运行 `make check_webget` 命令进行自动测试。
  - 完成编码工作。

*注意点：*
- 在 HTTP 中，每行必须以 `"\r\n"` 结尾。
- `Connection: close` 这句代码必须包含在客户端的请求中。
- 确保从服务器读取和打印所有的输出，直到套接字到达 "EOF"，即文件的末尾。

- 可靠字节流：实现该实验的第二个任务，完成 ByteStream 的代码编写工作，ByteStream 的功能在上面已经做了一定的介绍。
  - 打开 `libsponge/byte_stream.hh` 以及 `libsponge/byte_stream.cc` 文件，并完成接口内的方法的实现。
  - #[
      完成 writer 的方法，如下：

      ```cpp
      // Write a string of bytes into the stream. Write as many
      // as will fit, and return the number of bytes written.
      size_t write(const std::string &data);

      // Returns the number of additional bytes that the stream has space for
      size_t remaining_capacity() const;

      // Signal that the byte stream has reached its ending
      void end_input();

      // Indicate that the stream suffered an error
      void set_error();
      ```
    ]
  - #[
      完成 reader 的方法，如下：
      ```cpp
      // Peek at next "len" bytes of the stream
      std::string peek_output(const size_t len) const;

      // Remove "len" bytes from the buffer
      void pop_output(const size_t len);

      // Read (i.e., copy and then pop) the next "len" bytes of the stream
      std::string read(const size_t len);

      bool input_ended() const;   // `true` if the stream input has ended
      bool eof() const;           // `true` if the output has reached the en
      ```
    ]

  - 完成 byte_stream 中代码的编写后，运行 `make check_lab0` 命令进行自动测试。

- 温馨提示：当你在开发代码的时候，可能会遇到无法解决的问题，下面给出解决的办法。
  - 运行 `cmake .. -DCMAKE_BUILD_TYPE=RelASan` 命令配置 build 目录，使编译器能够检测内存错误和未定义的行为并给你很好的诊断。
  - 你还可以使用 valgrind 工具。
  - 你也可以运行 `cmake .. -DCMAKE_BUILD_TYPE=Debug` 命令配置并使用 GNU 调试器（gdb）。
  - 你可以运行 `make clean` 和 `cmake .. -DCMAKE_BUILD_TYPE=Release` 命令重置构建系统。
  - 如果你不知道如何修复遇到的问题，你可以运行 `rm -rf build` 命令删除 build 目录，创建一个新的 build 目录并重新运行 `cmake ..` 命令。

== 实验数据记录和处理

#text(fill: red)[以下实验记录均需结合屏幕截图（截取源代码或运行结果），进行文字标注（看完请删除本句）。]

- 第二步中抓取网页的运行结果

#v(5em)

- 编写的 webget 关键代码，即 `get_URL` 中的代码

#v(5em)

- 使用 webget 抓取网页运行结果

#v(5em)

- 运行 `make check_webget` 的测试结果展示

#v(5em)

- 实现 ByteStream 关键代码截图（描述总体，省略细节部分）

#v(5em)

- 运行 `make check_lab0` 测试结果。

#v(5em)

== 实验结果分析

#text(fill: red)[根据你编写的程序运行效果，分别解答以下问题（看完请删除本句）。]

- 完成 webget 程序编写后的测试结果和 Fetch a Web page 步骤的运行结果一致吗？如果不一致的话你认为问题出在哪里？请描述一下所写的 webget 程序抓取网页的流程。

#v(5em)

- 请描述 ByteStream 是如何实现流控制的？

#v(5em)

- 当遇到超出 capacity 范围的数据流的时候，该如何进行处理？如果不限制流的长度的时候该如何处理？

#v(5em)

== 思考与总结

#text(fill: red)[实验过程中遇到的困难，得到的经验教训，对本实验安排的更好建议（看完请删除本句）。]

