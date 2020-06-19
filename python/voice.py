#!/usr/bin/python

import speech_recognition

recognizer = speech_recognition.Recognizer()
with speech_recognition.Microphone() as source:
    print("Say something!\n")
    audio = recognizer.listen(source)

print("Google Speech Regcognition thinks you said:")
print(recognizer.recognize_google(audio))
