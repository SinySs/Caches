import random as rnd

def search_next(n, arr, size):
    for i in range(n+1, len(arr)):
        if arr[i] == arr[n]:
            return i
    return size + 1

f_data = open('data.txt', 'w')
f_answer = open('answers.txt', 'w')
for j in range(5):

    size = rnd.randint(1, 20)
    max_number = rnd.randint(4, 10)
    cash_size = rnd.randint(1, 5)
    arr = []
    cash = []



    for i in range(size):
            arr.append(rnd.randint(1, max_number))


    hits = 0
    history = [-1] * cash_size

    for i in range(size):
        #print("start cash" + str(cash))
        #print("enter:" + str(arr[i]))
        if arr[i] in cash:
            history[cash.index(arr[i])] = search_next(i, arr, size)
            hits += 1

        else:
            if len(cash) < cash_size:
                cash.append(arr[i])
                history[cash.index(arr[i])] = search_next(i, arr, size)
            else:
                if search_next(i, arr, size) < max(history):
                    cash[history.index(max(history))] = arr[i]
                    history[cash.index(arr[i])] = search_next(i, arr, size)
        #print("cash" + str(cash))
        #print(history)
    f_data.write(str(cash_size) + ' ' + str(size) + '\n')
    for i in range(size):
        f_data.write(str(arr[i]) + ' ')
    f_data.write('\n')
    

    f_answer.write(str(hits) + '\n')
f_data.close()
f_answer.close()
