import json #Подключаем библиотеку json, в отличии от языка С++ она встроена
with open('in.json', 'r') as f:
    j = json.load(f)
out = []
for task in j:
    userId    = task['userId'] #получаем id и статус выполнения
    completed = task['completed']
    selectedUser = None
    for user in out:
        if user['userId'] == userId: #Ищем пользователя с id userID
            selectedUser = user
            break
    if selectedUser == None:
        selectedUser = {}
        selectedUser['userId'] = userId
        selectedUser['task_completed'] = 0
        out.append(selectedUser) #Добавляем последним элементом, если не нашли
    if completed:
        selectedUser['task_completed'] += 1 #При выполненом задании повышаем счетчик
with open('out.json', 'w') as f: #Выводим в файл выхода
    f.write(json.dumps(out, indent=2))