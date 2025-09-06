![Logo](https://github.com/BlakeGurnee/BagelsAfterMidnight_PushBackCodeRepository/blob/main/Bagels%20After%20Midnight.png)

# 📢 8031B Bagles After Midnight - 2025 - 2026 "Push Back" Code Repository

Welcome to the official codebase for 8031B Bagels After Midnight's robot in the 2025 - 2026 VEX Robotics competition, "Push Back." Here lies the source code for our robot, written in C++ using the PROS development environment and the Lemlib Template.

We use Git and GitHub for version control, allowing us to:

- ✅ Organize — Our code is divided into logical, clearly-named files.
- ✅ Track changes — Easily revert to previous versions if something goes wrong.
- ✅ Back up our work — Our code is safely stored in the cloud, so it doesn't get lost. It enables our development to be faster, more efficient, and truly collaborative. 🚀

---

## 🚀 Key Features

Our robot is equipped with advanced features to dominate the "Push Back" competition. Here’s a look at what makes our code stand out:

### 🎯 Block Detection

This uses an optical sensor for block detection and classification for accurate placement.

### 🔄 PID Control

Proportional, Integral, and Derivative control ensures accurate motor movements and alignment.

### 🧠 Sensor Integration

Our robot is equipped with a diverse array of sensors to enhance the robot's performance:

- 🔵 Optical Sensor — To sort out wrong color blocks.
- 🔵 Inertial Sensor — Keeps track of orientation and ensures that turns are accurate.
- 🔵 Rotation Sensor — Works with odometry and PID with a tracking wheel to ensure precise movement during autonomous.
- 🔵 Distance Sensor — Detects obstacles and helps with autonomous alignment.
- 🔴 Stall Detection — Monitors motor load and movement to prevent stalls, protecting hardware and improving reliability.

### 🛠️ Autonomous Selector

We have implemented a user-friendly autonomous selector for flexibility during matches. This feature allows us to:

- Choose from multiple preprogrammed autonomous routines directly from the robot’s brain.
- Customize the strategy based on the starting position and the opponent’s layout.
- Have easy access to multiple autons all on the same program.
- Print critical information and errors to the console.
- Display our team's logo on the brain during matches.

The selector interface is intuitive, ensuring smooth operation even under time constraints.

### 💪 Autonomous Skills Path Optimization

To maximize performance in autonomous skills challenges, we use Pure Pursuit path-following algorithms. This ensures:

- Highly accurate path tracking, even with complex curves.
- Optimal speed adjustments for the fastest possible completion times.
- Reliable and consistent execution across multiple runs.

### 📝 Controller Input Recording and Playback (New!)

Our latest addition allows recording operator control inputs during skills runs and playing them back autonomously, enabling:

- Capturing precise joystick and button states during driver control for perfect replication.
- Saving recordings persistently on the robot’s SD card, allowing playback even after power cycles.
- Easy toggling of recording mode in the main code (disabled by default to prevent accidental recording).
- Future improvements to autonomous routines based on actual driver performance.

---

## 📚 File Structure

To keep our project maintainable and easy to navigate, we’ve organized the files into a simple, intuitive structure:

📂 src/  
┣ 📜 main.cpp           // Main entry point for our robot's code  
┣ 📜 autons.cpp         // Autonomous routines for all field positions  
┣ 📜 auton_utils.cpp    // Controller input recording and playback utilities  
┣ 📜 globals.cpp        // Global variables and constants  
┗ 📜 helpers.cpp        // Reusable helper functions for code efficiency  

📂 include/  
┣ 📜 globals.hpp        // Header file for global variables and constants  
┣ 📜 auton_utils.hpp    // Header declarations for recording/playback  
┗ 📜 helpers.hpp        // Header file for helper functions  

📂 docs/                 // Documentation and notes for the codebase  
📂 tests/                // Test scripts and prototypes for new features  

---

## 💡 FAQ (Frequently Asked Questions)

#### 🔹 Are the programs cleanly written, well-commented, and easy to follow?

Yes! Our code is clean, well-organized, and well-documented. Every major section of the code is labeled as such, making it easier for both new and advanced members to understand. We also apply modular design by separating our logic into dedicated files for autonomous routines, global variables, and helper functions.

#### 🔹 Is the programming effective at solving game challenges for Qualification Matches and Autonomous Skills Challenges?

Absolutely! Our program is battle-tested and competition-ready. Here’s how we dominate both modes:

### Autonomous in Qualification Matches  
Our program enables the robot to:

- Intake blocks from match loaders
- Put blocks inside the long goal
- Put blocks inside the center goal

This earns us the autonomous win point and works for all four starting positions on the field with minimal error.

### Autonomous Skills  
- Prioritizes speed and precision to ensure consistency and high scores in skills runs.

---

## 📈 Version Control with GitHub

How we use GitHub for version control:

- 🌿 Feature Branches: Every new feature or change starts in a new branch (like `feature/PID-tuning`) to avoid disrupting the main code.
- 🔍 Pull Requests & Code Reviews: Code is reviewed before being merged into the main branch to ensure it works properly.
- 🏷️ Release Tags: We tag stable versions (such as: `v1.0.0`) so we can track our progress over time.

🕵️‍♂️ Check our commit history to see how our code has evolved to solve key challenges.

---

## 📕 Documentation

[Documentation](Coming Soon!)

---

## 📲 Contact Us

Curious about anything, have a suggestion, or want to connect? Feel free to hit us up on Instagram! We're always keen on sharing our journey, learning from others, and inspiring the next generation of robotics champions.
