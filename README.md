## Introduction
> This repo contains code about my Bachelor's Thesis.

- Goal is to detect emotions using pupil measures and iris location with Machine Learning.
- Written in C++ (CXX17).

## Project Structure
```
.
├── asset                                           => Cascades
│   ├── haarcascade_eye_tree_eyeglasses.xml
│   ├── haarcascade_eye.xml
│   └── haarcascade_frontalface_alt.xml
├── data        
│   ├── raw                                         => Raw Images
│   │   └── happy
│   │       ├── 001.jpg
│   │       ├── 002.jpg
│   │       ├── 003.jpg
│   │       └── 004.jpg
│   └── result                                      => Processed Images
│       ├── 62A93ZEumcFdXBkV.jpg
│       ├── Qa63I5Rt2O4XzkhE.jpg
│       ├── sdPBtyKIbL3eqjTZ.jpg
│       └── wBR4ve6zZGKoN7US.jpg
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
- g++
```

- Clone the repository

```shell
$ git clone https://github.com/redgroot/pupil-emotion-detection.git
```

- Provide full paths in:
    - main.cpp


- Run
```shell
$ cmake .
```
## Roadmap
- [x] Load images,
- [x] Detect face,
- [x] Detect eye,
- [x] Draw ellipses around face and eye,
- [ ] Detect iris,
- [ ] Detect pupil,
- [ ] Draw ellipses around iris and pupil,
- [ ] Measure distance between eye frame and iris then get location,
- [ ] Measure diameter of iris and pupil,
- [ ] Implement ML algorithm for training based on emotion categories/wheel with processed images.
    
## License

- Licensed under the MIT license. See in [LICENSE.md](LICENSE.md).
