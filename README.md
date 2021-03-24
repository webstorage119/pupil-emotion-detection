## Introduction
> This repo contains codes of my Bachelor's Thesis.

- Goal is to detect emotions using pupil measures and iris location with Machine Learning (Caffe) and Image Processing (OpenCV).
- Written in C++ (CXX17).

## Project Structure
```
.
├── asset                                           => Cascades
│   ├── haarcascade_eye_tree_eyeglasses.xml
│   ├── haarcascade_eye.xml
│   └── haarcascade_frontalface_alt.xml
├── data        
│   ├── raw                                         => Raw Images (Dataset)
│   │   └── happy
│   │       ├── 001.jpg
│   │       ├── 002.jpg
│   │       ├── 003.jpg
│   │       └── 004.jpg
│   └── result                                      => Processed Images for visual approval.
│       └── happy
│           ├── 62A93ZEumcFdXBkV.jpg
│           ├── Qa63I5Rt2O4XzkhE.jpg
│           ├── sdPBtyKIbL3eqjTZ.jpg
│           └── wBR4ve6zZGKoN7US.jpg
├── include                                         => Header Files
│   └── image.h
├── src                                             => Source Files
│   └── image.cpp
├── CMakeLists.txt
├── main.cpp
├── LICENSE.md 
└── README.md
```

## Development

- I highly recommend using **Linux** for developing.
- Install dependencies.

```
- opencv
- hdf5
- vtk
- cmake
- gcc
- cuda
- caffe (cuda)
```

- For Arch Linux you can type this to install dependencies.
  - ```shell
    $ sudo pacman -S opencv hdf5 vtk cmake gcc cuda
    $ yay -S caffe-cuda # replace yay with your preferred aur helper
    ```

- Clone the repository

```shell
$ git clone https://github.com/redgroot/pupil-emotion-detection.git
```

- Provide full paths in:
    - [main.cpp](main.cpp)


- Compile & Run
  - ```shell
    $ cmake .
    $ make
    ```
  - Or if you are using [CLion](https://www.jetbrains.com/clion/) like me, open project then click to play button in the top right.

## Roadmap
- [x] Load images,
- [x] Detect face,
- [x] Detect eye,
- [x] Draw ellipses around face and eye,
- [ ] Detect iris,
- [ ] Detect pupil,
- [ ] Draw ellipses around iris and pupil,
- [ ] Measure distance between eye frame and iris to get location,
- [ ] Measure diameter of iris and pupil,
- [ ] Convert OpenCV Mat to Caffe Datum,
- [ ] Create annotations,  
- [ ] Implement ML algorithm (convolutional neural networks) for training based on emotion categories/wheel.
    
## License

- Licensed under the MIT license. See in [LICENSE.md](LICENSE.md).
