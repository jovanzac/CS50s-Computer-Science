import gensim
import json
import numpy as np
from nltk.tokenize import word_tokenize, sent_tokenize


def most_similar_text(class_index, mssg) :
    with open("data//intents.json","r") as outfile :
        intents = json.load(outfile)["intents"]

    # consider the class at class_index
    patterns = intents[class_index]["patterns"]
    response = intents[class_index]["responses"]
    words = [[word.lower() for word in word_tokenize(text)] for text in patterns]

    dictionary = gensim.corpora.Dictionary(words)

    # create a bag of words
    corpus = [dictionary.doc2bow(word) for word in words]

    # TFIDF
    # Words that occur more frequently get smaller weights
    tf_idf = gensim.models.TfidfModel(corpus)

    # Creating similarity measure object
    # Building the index
    sims = gensim.similarities.Similarity("workdir/", tf_idf[corpus], num_features=len(dictionary))

    query_words = [word.lower() for word in word_tokenize(mssg)]
    query_bow = dictionary.doc2bow(query_words)

    query_tf_idf = tf_idf[query_bow]

    similarity = list(sims[query_tf_idf])
    index_most_similar = similarity.index(max(similarity))
    
    # return index of the most similar text, the most similar text and the responses corresponding to is
    return index_most_similar, patterns[index_most_similar], response[index_most_similar]

if __name__ == "__main__" :
    index_most_similar, pattern, response = most_similar_text(0)

    print(f"index_most_similar: {index_most_similar}")
    print(f"Most similar pattern: {pattern}")
    print(f"response will be: {response}")