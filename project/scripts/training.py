import random
import json
import pickle
import numpy as np

import nltk
from nltk.stem import WordNetLemmatizer

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Activation, Dropout
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.utils import to_categorical

lemmatizer = WordNetLemmatizer()

intents = json.loads(open("data//intents.json").read())

words = []
classes = []
documents = []
ignore_chars = [".", "?", "'", "-", "!"]

for intent in intents["intents"] :
    for pattern in intent["patterns"] :
        words_list = nltk.word_tokenize(pattern)
        words.extend(words_list)
        documents.append((words_list, intent["tag"]))
        if intent["tag"] not in classes :
            classes.append(intent["tag"])


words = [lemmatizer.lemmatize(word) for word in words if word not in ignore_chars]
words = sorted(set(words))

classes = sorted(set(classes))

pickle.dump(words, open("data//words.pkl", "wb"))
pickle.dump(classes, open("data//classes.pkl", "wb"))

training = []
out_empty = [0] * len(classes)

for doc in documents :
    bag = []
    word_patterns = doc[0]
    word_patterns = [lemmatizer.lemmatize(word.lower()) for word in word_patterns]
    for word in words :
        bag.append(1) if word in word_patterns else bag.append(0)
    out_row = list(out_empty)
    out_row[classes.index(doc[1])] = 1
    training.append([bag, out_row])

random.shuffle(training)
training = np.array(training)

train_x = list(training[:, 0])
train_y = list(training[:, 1])

model = Sequential()
model.add(Dense(128, input_shape=(len(train_x[0]),), activation="relu"))
model.add(Dropout(0.5))
model.add(Dense(64, activation="relu"))
model.add(Dropout(0.5))
model.add(Dense(len(train_y[0]), activation="softmax"))

sgd = SGD(lr=0.01, decay=1e-6, momentum=0.9, nesterov=True)
model.compile(loss="categorical_crossentropy", optimizer=sgd, metrics=["accuracy"])


hist = model.fit(np.array(train_x), np.array(train_y), epochs=200, batch_size=5, verbose=1)

model.save("data//chatbot_model.h5", hist)

print("Done")