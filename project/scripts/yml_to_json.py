import yaml
import json
import os


dict_intents = {
    "intents": []
}


for file in os.listdir('./data//yml_files') :
    yaml_file = open(f"data//yml_files//{file}", 'r')
    yaml_content = yaml.load(yaml_file)

    tag = None
    patterns = list()
    responses = list()

    for key, value in yaml_content.items():
        if key == "categories" :
            tag = value[0]

        elif key == "conversations" :
            for conversation in value :
                if conversation[0] in patterns :
                    responses[patterns.index(conversation[0])].append(conversation[1])
                else :
                    patterns.append(conversation[0])
                    responses.append([conversation[1]])

            intents = {
                "tag": tag,
                "patterns": patterns,
                "responses": responses
            }
            dict_intents["intents"].append(intents)

# Serializing json andwriting it to a file
json_object = json.dumps(dict_intents, indent = 1)
with open("./data//intents.json", "w") as outfile:
    outfile.write(json_object)