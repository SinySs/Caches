import random as rnd

def minn(arr):
    min_ = arr[0]
    n = 0
    for i in range(len(arr)):
        if arr[i] <= min_:
            min_ = arr[i]
            n = i
    return n
f_data = open('data.txt', 'w')
f_answer = open('answers.txt', 'w')

for j in range(5):

    size = rnd.randint(1, 20)
    max_number = rnd.randint(4, 10)
    cash_size = rnd.randint(2, 5)
    arr = []
    cash = []
    freq = [0] * cash_size
    hits = 0



    for i in range(size):
            arr.append(rnd.randint(1, max_number))

    for i in range(size):
        #print("CASH:")
        #print(cash)
        #print("Freq:")
        #print(freq)
        if arr[i] in cash:
            freq[cash.index(arr[i])] += 1
            n = cash.index(arr[i])
            for j in range(len(cash)):
                if (freq[j] == freq[cash.index(arr[i])]) and (n > j):
                    cash.insert(j, arr[i])
                    cash.pop(n+1)
                    break;
                
                
                
            hits += 1
        else:
            if len(cash) < cash_size:
                cash.insert(0, arr[i])
                freq.insert(0, 0)
                freq.pop(cash_size)
                
            else:
                n = minn(freq)
                cash.pop(n)
                freq.pop(n)
                cash.insert(0, arr[i])
                freq.insert(0, 0)

    f_data.write(str(cash_size) + ' ' + str(size) + '\n')
    for i in range(size):
        f_data.write(str(arr[i]) + ' ')
    f_data.write("\n")
    

    f_answer.write(str(hits) + '\n')
f_data.close()
f_answer.close()
