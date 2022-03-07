  <h3 align="center">The Raiders: Acceleration Measuring Knee Pad</h3>

  <p align="center">
    Knee pad built to measure acceleration of the lower legs to detect walking imbalances <br />
  (Pivoted from Collision detection helmet)
    <br />
    <a href="https://github.com/djstroud97/TheRaiders-SeniorDesignII"><strong>Explore the docs »</strong></a>
    <br />
    <br />
  </p>
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#How-it-works">How it works</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
During the first semester, our project was to design and build a collision detection helmet that would measure the acceleration of the head/helmet during a collision and alert appropriate staff whenever there was a potential concussive impact.
However, we encountered multiple challenges and difficulties in our implementation. In order to detect a concussive impact the range of acceleration that the accelerometer needed to detect would
be around +-100 G's. This severely limited the amount of accelerometers we could use. Unfortunately, we received defective hardware which included more than 3 sensors that either had defects
that we only found after we had received the sensors. These sensors had known issues about calibration and we were not able to solve them even after browsing through forums,
consulting professors and mentors, and even contacting the manufacturer's support team.

From there, we decided to pivot our project (after approval from our professor) from the helmet to another project that used similar theory about measuring acceleration. Enter, the knee pad.
The team would decide that we could use the same concept and apply it to a kneepad. People who experience issues or accidents that result in them needing to relearn how to walk. 
Sometimes, a lot of the walking habits we form have long term consequences on our joints and muscles. Although most habits can be seen by the eye of a trained physical therapist, some habits suck as uneven 
load distribution on the legs might be hard to detect. Our project attempts to tackle the problem by measuring the acceleration of the lower segment of the wearer's legs and comparing 
them. The data would then be passed to a professional for corrective actions. This would not only be able to help the patient but also assist the medical professional in accurate and proper diagnosis.

__Note: Due to our pivot to a different project in the second semester, a lot of our documentation and works are slightly out of date. This has been alerted to Professor Stallard and will be updated soon__


### How it Works

The project consists of a microcontroller and  2 accelerometers. We chose the Arduino Nano due to its compact size yet ample processing power and also the amount of support and documentation
there is for the microcontroller. The sensors we used are the MPU6050, they are 6 - depth of field sensors which are 3 axis accelerometer and 3 axis gyroscope. This small sensor has the range of +-16 G's which 
is more than enough to detect the unseen differences of steps of the wearer. 

The sensor provides acceleration of the knees to the microcontroller, which runs a sketch that converts the raw values to acceleration relative to gravity or 'g-force' (G). The sketch then saves the data
by writing the data onto an storage device (in our case, we used an SD card). The data on the storage device can then be plotted on a graph for ease of analysis.



### Built With

* []()Arduino Code
* []()Arduino Nano
* []()MPU6050 Accelerometer/Gyro


<!-- ROADMAP -->
## Roadmap
- As mentioned previously, this project was created after the team pivoted from the initial helmet project. Due to that, we've had limited time to work on the functionality and features 
of the knee pad. Currently, we have a sensor wired to the microcontroller to detect acceeleration. The sketch used to collect, convert and compare data is still in development and currently 
can convert the raw values of the sensor to G's.

Planned Additions:
- **Attaching a second sensor to the microcontroller to collect data from other knee**<br/> 
Another MPU6050 needs to be connected to the microcontroller so that we could collect data from the other knee for proper comparison.

- **Ergonomics and placement of the components**<br/>
As the project involves multiple components that need to be worn by the wearer, we need to place the components in a way where it can accurately read the acceleration of the knee whilst 
not obstructing the mobility and movement of the wearer.

- **Software improvements regarding data collection and writing it to the storage device**<br/>
Due to the hardware only recently being completed, there was limited time for software development. Currently, features including implementation of the second sensor and function to write the
data onto the storage device are in development.



<!-- CONTACT -->
## Contact

Project Link: [https://github.com/djstroud97/TheRaiders-SeniorDesignII](https://github.com/djstroud97/TheRaiders-SeniorDesignII)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements
* []() Collaborative effort by Julian T, Dallas S, Isuru Y, Ali A.


* []() README developed by Julian T.





