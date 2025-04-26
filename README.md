📢 8031A Midnight Bagles - 2025 - 2026 "Push Back" Code Repository
Welcome to the official codebase for 8031A Midnight Bagles' robot in the 2025 - 2026 VEX Robotics competition, "Push Back." Here lies the source code for our robot, written in C++ using the PROS development environment and the Lemlib Template.

We use Git and GitHub for version control, allowing us to:

✅ Organize — Our code is divided into logical, clearly-named files.

✅ Track changes — Easily revert to previous versions if something goes wrong.

✅ Back up our work: Our code is safely stored in the cloud so it doesn't get lost. It makes our development way faster, highly efficient, and truly collaborative.

It makes our development faster, more efficient, and more collaborative. 🚀

🚀 Key Features
Our robot is equipped with advanced features to dominate the "High Stakes" competition. Here’s a look at what makes our code stand out:

🎯 Ring Detection
This uses an optical sensor for ring detection and classification for accurate placement.

🔄 PID Control
Proportional, Integral, and Derivative control ensures accurate motor movements and alignment.

🧠 Sensor Integration
Our robot is equipped with a diverse array of sensors to enhance the robot's performance:

🔵 Optical Sensor - To sort out wrong color rings.
🔵 Inertial Sensor — Keeps track of orientation and ensures that turns are accurate.
🔵 Rotation Sensor — Measures our ladybrown's position for precision movements.
🔵 Distance Sensor — Detects obstacles and helps with autonomous alignment.
🔵 Limit Switch — Detects when ladybrown hits it and sets it's position back to zero just in case the rotation sensor gets out of tune.
🛠️ Autonomous Selector
We have implemented a user-friendly autonomous selector for flexibility during matches. This feature allows us to:

Choose from multiple preprogrammed autonomous routines directly from the robot’s brain.

Customize the strategy based on the starting position and opponent’s layout.

Have easy access to multiple autons all on the same program.

The selector interface is intuitive, ensuring smooth operation even under time constraints.

💪 Autonomous Skills Path Optimization
To maximize performance in autonomous skills challenges, we use Pure Pursuit path-following algorithms. This ensures:

Highly accurate path tracking, even with complex curves.

Optimal speed adjustments for the fastest possible completion times.

Reliable and consistent execution across multiple runs.

📚 File Structure
To keep our project maintainable and easy to navigate, we’ve organized the files into a simple, intuitive structure:

📂 src/
┣ 📜 main.cpp // Main entry point for our robot's code
┣ 📜 autons.cpp // Autonomous routines for all field positions
┣ 📜 globals.cpp // Global variables and constants
┗ 📜 helpers.cpp // Reusable helper functions for code efficiency

📂 include/
┣ 📜 globals.hpp // Header file for global variables and constants
┗ 📜 helpers.hpp // Header file for helper functions

📂 docs/ // Documentation and notes for the codebase
📂 tests/ // Test scripts and prototypes for new features

💡 FAQ (Frequently Asked Questions)
🔹 Are the programs cleanly written, well-commented, and easy to follow?
Yes! Our code is clean, well-organized, and well-documented. Every major section of the code is labeled as such, so that it's easier for new or advanced members to look at and understand. We also apply modular design by separating our logic into dedicated files for autonomous routines, global variables, and helper functions.

🔹 Is the programming effective at solving game challenges for Qualification Matches and Autonomous Skills Challenges?
Absolutely! Our program is battle-tested and competition-ready. Here’s how we dominate both modes:

Autonomous in Qualification Matches
Our program enables the robot to:

Score a ring on the alliance wall stake.
Place two rings on a mobile goal.
Touch the center ladder
This earns us the autonomous win point and it works for all four starting positions on the field with minimal error.

Autonomous Skills
Prioritizes speed and precision to ensure consistency and high scores in skills runs.
📈 Version Control with GitHub
How we use GitHub for version control:

🌿 Feature Branches: Every new feature or change starts in a new branch (like feature/PID-tuning) to avoid disrupting the main code.
🔍 Pull Requests & Code Reviews: Code is reviewed before being merged into the main branch to ensure it works properly.
🏷️ Release Tags: We tag stable versions (such as: v1.0.0) so we can track our progress over time.
🕵️‍♂️ Check our commit history to see how our code has evolved to solve key challenges.

📕 Documentation
Documentation

📲 Contact Us
Curious about anything, have a suggestion, or want to connect? Feel free to hit us up on Instagram! We're always keen on sharing our journey, learning from others, and inspiring the next generation of robotics champions.
