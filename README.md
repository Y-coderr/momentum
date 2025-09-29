# 🚀 Momentum Physics Engine

A modern 3D physics engine built with OpenGL and C++, featuring real-time physics simulation, particle systems, and an intuitive debug interface.

![Physics Engine Demo](demo.gif)

## ✨ Features

- **💪 Robust Physics Simulation**
  - 🔄 Real-time rigid body dynamics
  - 🎯 Configurable elasticity and friction
  - 💥 Accurate collision detection and response
  - 💤 Sleep optimization for inactive objects

- **🌟 Particle System**
  - 🎆 Configurable particle emitters
  - ⚡ Physics-based particle behavior
  - 🎯 Particle-object collision handling

- **🎛️ Interactive Debug Interface**
  - 🔧 Real-time physics parameter adjustment
  - 🎮 Object creation and manipulation
  - 📊 Performance statistics and monitoring
  - 🔍 Debug visualization options

## 🛠️ Tech Stack

- **🔧 Core Technologies**
  - 💻 C++17
  - 🎮 OpenGL 4.6
  - 🪟 GLFW (Window management)
  - ⚡ GLAD (OpenGL loader)
  - 🖥️ ImGui (Debug interface)
  - 🧮 Eigen (Math operations)
  - 🏗️ CMake (Build system)

## 📋 Prerequisites

- C++17 compatible compiler
- CMake 3.10 or higher
- OpenGL 4.6 compatible GPU
- Git

### 💻 System-Specific Requirements

#### 🍎 macOS
```bash
# Install dependencies using Homebrew
brew install cmake
brew install eigen
brew install glfw3
```

#### 🐧 Linux (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install cmake
sudo apt-get install libeigen3-dev
sudo apt-get install libglfw3-dev
sudo apt-get install libgl1-mesa-dev
```

#### 🪟 Windows
- Install [Visual Studio](https://visualstudio.microsoft.com/) with C++ development tools
- Install [CMake](https://cmake.org/download/)
- The required libraries are included in the repository

## 🚀 Installation

1. 📥 Clone the repository:
   ```bash
   git clone https://github.com/Y-coderr/momentum.git
   cd momentum
   ```

2. 📁 Create and navigate to build directory:
   ```bash
   mkdir build
   cd build
   ```

3. 🔨 Configure and build the project:
   ```bash
   cmake ..
   make
   ```

4. ▶️ Run the application:
   ```bash
   ./momentum
   ```

## 🎮 Usage

### 🕹️ Basic Controls
- **Space**: ⏯️ Play/Pause simulation
- **Left Mouse Button + Drag**: 🔄 Rotate camera
- **Right Mouse Button + Drag**: 🔁 Pan camera
- **Scroll Wheel**: 🔍 Zoom in/out
- **Shift**: 🔄 Toggle object movement mode

### 🛠️ Debug Interface
1. 📊 Use the "Debug Info" panel to monitor:
   - 📈 Total object count
   - 🔄 Active/sleeping object count
   - ⚡ Performance metrics

2. 🎯 Object Creation:
   - 📦 Select object type (Cube/Sphere)
   - ⚙️ Adjust physical properties
   - 🎮 Click "Create" to spawn object

3. 🎛️ Physics Parameters:
   - 🌍 Gravity strength
   - 💫 Restitution coefficients
   - ⚡ Friction values

## 🏗️ Architecture

The engine is built with a modular architecture:

- **🎯 Core Engine**
  - ⚙️ Physics simulation loop
  - 💥 Collision detection system
  - 📦 Object management

- **🎨 Rendering System**
  - 🖥️ OpenGL-based renderer
  - 🎥 Camera management
  - 🔍 Debug visualization

- **🎛️ User Interface**
  - 🖥️ ImGui integration
  - 🎮 Real-time controls
  - 📊 Debug information display

## 🤝 Contributing

1. 🔱 Fork the repository
2. 🌿 Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. 💾 Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. 🚀 Push to the branch (`git push origin feature/AmazingFeature`)
5. 📬 Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- 🎛️ ImGui for the debug interface
- 🧮 Eigen for vector mathematics
- 🪟 GLFW for window management
- 🌟 The OpenGL community for resources and documentation

## 📬 Contact

Yash Kadam - [@Y-coderr](https://github.com/Y-coderr)

🔗 Project Link: [https://github.com/Y-coderr/momentum](https://github.com/Y-coderr/momentum)

## Architecture

The engine is built with a modular architecture:

- **Core Engine**
  - Physics simulation loop
  - Collision detection system
  - Object management

- **Rendering System**
  - OpenGL-based renderer
  - Camera management
  - Debug visualization

- **User Interface**
  - ImGui integration
  - Real-time controls
  - Debug information display

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- ImGui for the debug interface
- Eigen for vector mathematics
- GLFW for window management
- The OpenGL community for resources and documentation

## Contact

Yash Kadam - [@Y-coderr](https://github.com/Y-coderr)

Project Link: [https://github.com/Y-coderr/momentum](https://github.com/Y-coderr/momentum)