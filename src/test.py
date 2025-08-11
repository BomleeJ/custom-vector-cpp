import time



test_value = "This is my test string"
print("=====Executing Benchmark Test in Python=====")
print("Pushing Back 1,000,000 Test strings")
start = time.time()
for i in range(5):
    myList = []
    for i in range(1000000):
        myList.append(test_value)

end = time.time()

duration = (end - start) * 1000 / (5)  

print(f"Python Average over 5 trials {duration} ms")