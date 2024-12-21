import matplotlib.pyplot as plt
import json

dictionary = json.load(open('output.json', 'r'))

results_genetic = []
results_brute = []

# parse keys and values for 2 algorithms
for benchmark in dictionary["benchmarks"]:
    if benchmark["family_index"] == 0:
        results_genetic.append({
            "per_family_instance_index": benchmark["per_family_instance_index"],
            "real_time": benchmark["real_time"]
        })
    elif benchmark["family_index"] == 1:
        results_brute.append({
        "per_family_instance_index": benchmark["per_family_instance_index"],
        "real_time": benchmark["real_time"]
    })



# NO: We use 'per_family_instance_index' - because it's a non-repeating parameter.
# We should find min 'real_time' value on the graphic and than find optimal gyperparameters in name at json file 

# for genetic algo
x_values_gen = [item["per_family_instance_index"] for item in results_genetic]
y_values_gen = [item["real_time"] for item in results_genetic]

# auxilary func to determine range of min values for genetic (also can see in graph) 
dict_gen = {x_values_gen[i]: y_values_gen[i] for i in range(len(x_values_gen))}
sort_dict_gen = dict(sorted(dict_gen.items(), key=lambda item: item[1]))

#for brute-force
x_values_brute = [item["per_family_instance_index"] for item in results_brute]
y_values_brute = [item["real_time"] for item in results_brute]

# auxilary func to determine range of min values for brute-force (also can see in graph) 
dict_brute = {x_values_brute[i]: y_values_brute[i] for i in range(len(x_values_brute))}
sort_dict_brute = dict(sorted(dict_brute.items(), key=lambda item: item[1]))


print(list(sort_dict_gen.items())[:10])
print(list(sort_dict_brute.items())[:10])


## BAR GRAPH ##

fig = plt.figure()
plt.grid(True)

plt.bar(x_values_gen, y_values_gen, color='red', alpha=0.8)
plt.bar(x_values_brute, y_values_brute, color='green', alpha=0.4)

plt.xlabel('per_family_instance_index') 
plt.ylabel('real_time, us')
plt.title("Time measurement relative to gyperparams of 2 algorithms")

plt.legend(['Genetic algorithm', 'Brute-Force algorithm'])

fig.savefig('image.png', dpi=fig.dpi)
plt.show() 


