# Personal Assistant

## About
This is a simple personal assistant that can hold simple conversations and perform some simple tasks like tell the time,
date, open an application, etc.

This project has been made entirely using python.

This project was made as my final project for CS50x: Introduction to Computer Science. CS50 is Harvard University's
introduction to the intellectual enterprises of computer science and the art of programming for majors and non-majors alike,
with or without prior programming experience.



## Working
Run run.py to start the program. A simple gui interface has been implemented using tkinter for easy access and use.

The personal assistant is trained using tensorflow on a set of simple questions and corresponding answers. This model is
used to differentiate between different types of input the user may provide.

Input can be taken from the user in 2 ways via the gui. Either the user can type into an entry box or there is also an option
to accept voice input. The speech recognition part of this project is implemented using the speech_recognition library.

The PA responds to the users question/ command using the pyttsx3 library, for text to speech conversion. The PA's response is
also displayed on the GUI.



## Setup

### Contents
The scripts directory contains all the python files used in the creation of this program.

training.py and yml_to_json.py files are not needed for running the application. training.py was used to make the tensorflow
model and yml_to_json.py was used to convert all the conversations(which were obtained in yml format) into json for easier
access in the program.


### Libraries
requirements.txt contains all the dependencies required to run the application. Run the following command in terminal to install all the libraries required
to run this program.
```
pip install -r requirements.txt
```

Make sure that all the following packages are installed
1. tensorflow
2. tkinter
3. tkthemes
4. json
5. nltk
6. speech_recognition
7. pyttsx3


### Running it
To execute the program, run the following:
```
python run.py
```


## Video Demonstration
[![Alt text for your video](https://img.youtube.com/vi/FrlzSXRIK3Q/0.jpg)](https://youtu.be/FrlzSXRIK3Q)

Visit this url: https://youtu.be/FrlzSXRIK3Q



#### NOTE: This application is meant for Windows and has only been tested on Windows10


## About
This is a simple personal assistant that can hold simple conversations and perform some simple tasks like tell the time,
date, open an application, etc.

This project has been made entirely using python.

This project was made as my final project for CS50x: Introduction to Computer Science. CS50 is Harvard University's
introduction to the intellectual enterprises of computer science and the art of programming for majors and non-majors alike,
with or without prior programming experience.



## Working
Run run.py to start the program. A simple gui interface has been implemented using tkinter for easy access and use.

The personal assistant is trained using tensorflow on a set of simple questions and corresponding answers. This model is
used to differentiate between different types of input the user may provide.

Input can be taken from the user in 2 ways via the gui. Either the user can type into an entry box or there is also an option
to accept voice input. The speech recognition part of this project is implemented using the speech_recognition library.

The PA responds to the users question/ command using the pyttsx3 library, for text to speech conversion. The PA's response is
also displayed on the GUI.



## Setup

### Contents
The scripts directory contains all the python files used in the creation of this program.

training.py and yml_to_json.py files are not needed for running the application. training.py was used to make the tensorflow
model and yml_to_json.py was used to convert all the conversations(which were obtained in yml format) into json for easier
access in the program.


### Libraries
requirements.txt contains all the dependencies required to run the application. Run the following command in terminal to install all the libraries required
to run this program.
```
pip install -r requirements.txt
```

Make sure that all the following packages are installed
1. tensorflow
2. tkinter
3. tkthemes
4. json
5. nltk
6. speech_recognition
7. pyttsx3


### Running it
To execute the program, run the following:
```
python run.py
```


## Video Demonstration
[![Alt text for your video](https://img.youtube.com/vi/FrlzSXRIK3Q/0.jpg)](https://youtu.be/FrlzSXRIK3Q)

Visit this url: https://youtu.be/FrlzSXRIK3Q



#### NOTE: This application is meant for Windows and has only been tested on Windows10