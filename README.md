<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Thanks again! Now go create something AMAZING! :D
***
***
***
*** To avoid retyping too much info. Do a search and replace for the following:
*** CreatePhotonW, customftparser, @CreatePhotonW, email, CustomFTParser, Stateful FTP parser C++ library
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->
<!--
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]
-->


<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/CreatePhotonW/customftparser">
<!--    <img src="images/logo.png" alt="Logo" width="80" height="80"> -->
  </a>

  <h3 align="center">CustomFTParser</h3>

  <p align="center">
    Stateful FTP parser C++ library
    <br />
<!--    <a href="https://github.com/CreatePhotonW/customftparser"><strong>Explore the docs »</strong></a> -->
    <br />
    <br />
    <!--
    <a href="https://github.com/CreatePhotonW/customftparser">View Demo</a>
    ·
    -->
    <a href="https://github.com/CreatePhotonW/customftparser/issues">Report Bug</a>
    ·
    <a href="https://github.com/CreatePhotonW/customftparser/issues">Request Feature</a>
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!--
[![Product Name Screen Shot][product-screenshot]](https://example.com)
-->

Stateful FTP parser C++ library that exposes access to message parser state and message field values as each data segment is processed and parsed.


<!-- 
### Built With

* []()
* []()
* []()

-->



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

* cmake
* make

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/CreatePhotonW/customftparser.git
   ```
2. Change into the repo directory
   ```sh
   cd customftparser
   ```
3. Create build directory
   ```sh
   mkdir build
   ```
4. Change into the build directory
   ```sh
   cd build
   ```
5. Run cmake
   ```sh
   cmake ..
   ```
6. Run make
   ```sh
   make
   ```



<!-- USAGE EXAMPLES -->
## Usage
FTP request parser
```C++
std::string request_str = "SOMECOMMAND argument1 argument2\n";
auto parser = FTP::RequestParser();
std::vector<uint8_t> segment(request_str.begin(), request_str.end());
parser.process_segment(segment);
auto requests = parser.requests();
auto &request = requests[0].get();
//request.command();
//request.spacing1();
//request.arguments();
//request.lineending();
//request.serialized();
```
FTP reply parser
```C++
std::string reply_str = "227 Entering Passive Mode (10,2,8,240,7,166).\r\n";
auto parser = FTP::ReplyParser();
std::vector<uint8_t> segment(reply_str.begin(), reply_str.end());
parser.process_segment(segment);
auto replys = parser.replys();
auto &reply = replys[0].get();
//reply.code();
//reply.spacing1();
//reply.message();
//reply.lineending();
//reply.serialized();
```

_For more examples, please refer to the [tests.](test/main.cpp)_



<!-- ROADMAP -->
## Roadmap

See the [open issues](https://github.com/CreatePhotonW/customftparser/issues) for a list of proposed features (and known issues).



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

CreatePhotonW - [@CreatePhotonW](https://twitter.com/CreatePhotonW)

Project Link: [https://github.com/CreatePhotonW/customftparser](https://github.com/CreatePhotonW/customftparser)



<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/CreatePhotonW/repo.svg?style=for-the-badge
[contributors-url]: https://github.com/CreatePhotonW/repo/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/CreatePhotonW/repo.svg?style=for-the-badge
[forks-url]: https://github.com/CreatePhotonW/repo/network/members
[stars-shield]: https://img.shields.io/github/stars/CreatePhotonW/repo.svg?style=for-the-badge
[stars-url]: https://github.com/CreatePhotonW/repo/stargazers
[issues-shield]: https://img.shields.io/github/issues/CreatePhotonW/repo.svg?style=for-the-badge
[issues-url]: https://github.com/CreatePhotonW/repo/issues
[license-shield]: https://img.shields.io/github/license/CreatePhotonW/repo.svg?style=for-the-badge
[license-url]: https://github.com/CreatePhotonW/repo/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/CreatePhotonW
