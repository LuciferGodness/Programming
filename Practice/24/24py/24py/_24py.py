import json
from array import *
c = 0
i = 0
m ='a'
l = list('')
with open('in.json','r') as file:
    a = file.read()
    data = json.loads(a)
    h = dict(data[0])
    kol = h['userId']
    for t in range(len(data)):
        h = dict(data[l])
        if (kol == h['userId']):#Сравнение id
            if (h['completed']==1):#Проверка, кто выполнил задания
                c = с + 1
        else:
            d = {'userId':kol,
                'task_completed':c
            }
            l.append(m)
            l[i] = d
            p = p + 1
            c = 0
            kol  = h['userId']
            if (h['completed'] == 1):
                c = c + 1
    d={'userId':kol,
        'task_completed':c
    }
    l.append(m)
    l[i] = d            
print(l)
with open ('out.json','w') as fileend:
    fileend = json.dump(l, fileend, indent = 3)
  
