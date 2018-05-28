# LibraryChairControl

# Description of the project

### Problem

Students can not easily find an available chair or table in the library especially in the final weeks.Although the libraries includes many useful books, sources and papers, the libraries is used by students to studying, researching, and spending time alone.However, the capacity of the library may not be sufficient for these kinds of activities.
As a result, the libraries is not used in an efficient way.

### Solution

Using two LDR sensors -which are connected to Arduino Uno- one is for environment and the other is for seat, sending the data to cloud(Thingspeak) via ESP8266 Wi-Fi module and collecting data from the cloud via an Android application that determines a threshold for availability of the seat according to the value comes from the environment and shows whether the seat is available or not. Also, administration can decide a specific time (1,3,5,10 min etc.) to give permission to student for breaks. When students in a break, seat is in a "pending" state. When break time is finished, it becomes "available".

# Team Members

### Ahmet Ozan Tatlısu
I am senior computer engineering student at Bogazici University, I am going to start working as full stack developper at TechSign and will graduate in December hopefully :) I have knowledge about almost all popular programming languages like Java, Python, C/C++ , Android and JavaScript.
* E-mail : ahmetozan789@gmail.com / ozan.tatlisu@boun.edu.tr
* [Linkedin](https://www.linkedin.com/in/ahmet-ozan-tatlısu-635773139/)  

### Zeki Tel

Hello everyone, I'm Zeki TEL. I am studying Computer Engineering at Boğaziçi University.
 I am interested in Football, Basketball and other team sports. Also, I like playing computer games.
 I have worked on Python, Java, C/C++, and MATLAB
* E-mail : zeki.tel34@gmail.com / zeki.tel @boun.edu.tr
* [Linkedin](https://www.linkedin.com/in/zeki-tel-bb4325b7/)
* [Facebook](https://www.facebook.com/sfsdfasf)


### Mustafa Şişik

Hi guys, I am Mustafa Şişik, 4th grade Computer Engineering student at Boğaziçi University. I like watching comedy movies. I love Python and Android.

* E-mail: mustafa.sisik@boun.edu.tr

# Hardware setup
<img src="https://github.com/bounIoT/LibraryChairControl/blob/master/Figures/HardwareSetup.jpg">

# Flow of data 

<img src="https://github.com/bounIoT/LibraryChairControl/blob/master/Figures/FlowOfData.jpg">


# Development Environment

* Development Operating System: Ubuntu 16.04
* Development Tools: Arduino IDE, Thingspeak and Android Studio.
