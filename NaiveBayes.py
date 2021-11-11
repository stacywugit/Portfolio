import tkinter as tk
import csv
import random
import numpy as np
import math
import time

root = tk.Tk()
root.title("Naive Bayse")
root.geometry('300x450')

list_1 = []
acc = 0


def calculatenumerical(i, a, b):
    newarray = []
    for x in list_1:
        if x[16] == b:
            newarray.append(float(x[i]))
    mean = np.mean(newarray)
    var = np.var(newarray)
    result = (1/(math.sqrt(2*math.pi*var))*math.exp(0-((math.pow(float(a)-mean, 2))/(2*var))))
    return result


def calculatenominal(i, a, b):
    numofa = 0
    numofb = 0
    for x in list_1:
        if x[16] == b:
            numofb += 1
            if x[i] == a:
                numofa += 1
    return numofa/numofb


def possibility(x, cls):
    p = (calculatenumerical(0, x[0], cls)*calculatenominal(1, x[1], cls)*calculatenominal(2, x[2], cls) *
         calculatenominal(3, x[3], cls)*calculatenominal(4, x[4], cls)*calculatenumerical(5, x[5], cls) *
         calculatenominal(6, x[6], cls)*calculatenominal(7, x[7], cls)*calculatenominal(8, x[8], cls) *
         calculatenumerical(9, x[9], cls)*calculatenominal(10, x[10], cls)*calculatenumerical(11, x[11], cls) *
         calculatenumerical(12, x[12], cls)*calculatenumerical(13, x[13], cls)*calculatenumerical(14, x[14], cls) *
         calculatenominal(15, x[15], cls))
    return p


def hit_me():
    tStart = time.time()
    with open('bank.csv', newline='') as csvfile:
        rows = csv.reader(csvfile)

        rows = list(rows)
        random.shuffle(rows)
        a = len(rows)
        b = int(en.get())
        cut = int(a*b*0.01)
        global list_1
        list_1 = rows[:cut]
        list_2 = rows[cut:]

        i = 0
        result = []
        for x in list_2:
            y = possibility(x,'yes')
            n = possibility(x,'no')
            if y >= n:
                result.append('yes')
            else:
                result.append('no')
            i += 1
        tEnd = time.time()
        global acc
        TP = 0
        FP = 0
        FN = 0
        TN = 0
        j = 0
        for x in list_2:
            if x[16] == 'yes' and result[j] == 'yes':
                TP += 1
            elif x[16] == 'yes' and result[j] == 'no':
                FP += 1
            elif x[16] == 'no' and result[j] == 'yes':
                FN += 1
            else:
                TN += 1
            j += 1
        accuracy = round((TP+TN)/i, 3)
        errorrate = round(1 - (TP+TN)/i, 3)
        precision = round(TP/(TP+FP), 3)
        recall = round(TP/(TP+FN), 3)
        f1 = round(2*precision*recall/(precision+recall), 3)
        t = round(tEnd - tStart, 3)
        var1.set("Accuracy: " + format(accuracy))
        var2.set("Error Rate: " + format(errorrate))
        var3.set("Precision: " + format(precision))
        var4.set("Recall: " + format(recall))
        var5.set("F1-score: " + format(f1))
        var7.set("P     " + format(TP) + "       " + format(FP))
        var8.set("N     " + format(FN) + "       " + format(TN))
        var9.set("執行時間: " + format(t) + "秒")


var0 = tk.StringVar()
l0 = tk.Label(root, textvariable=var0)
var0.set("輸入要當training data的比例(%)")
l0.pack()


e = tk.StringVar()
en = tk.Entry(root, textvariable=e)
e.set('70')
en.pack()

bu = tk.Button(root, text='分類結果', width=15, height=2, command=hit_me)
bu.pack()

var1 = tk.StringVar()
l = tk.Label(root, textvariable=var1, bg='white', font=('Arial', 12), width=20, height=2)
var1.set("Accuracy: 0")
l.pack()

var2 = tk.StringVar()
l2 = tk.Label(root, textvariable=var2,  bg='white', font=('Arial', 12), width=20, height=2)
var2.set("Error Rate: 0")
l2.pack()

var3 = tk.StringVar()
l3 = tk.Label(root, textvariable=var3,  bg='white', font=('Arial', 12), width=20, height=2)
var3.set("Precision: 0")
l3.pack()

var4 = tk.StringVar()
l4 = tk.Label(root, textvariable=var4,  bg='white', font=('Arial', 12), width=20, height=2)
var4.set("Recall: 0")
l4.pack()

var5 = tk.StringVar()
l5 = tk.Label(root, textvariable=var5,  bg='white', font=('Arial', 12), width=20, height=2)
var5.set("F1-score: 0")
l5.pack()

var9 = tk.StringVar()
l9 = tk.Label(root, textvariable=var9,  bg='white', font=('Arial', 12), width=20, height=2)
var9.set("執行時間: 0秒")
l9.pack()

var6 = tk.StringVar()
l6 = tk.Label(root, textvariable=var6, font=('Arial', 12))
var6.set("   P'       N'")
l6.pack()

var7 = tk.StringVar()
l7 = tk.Label(root, textvariable=var7, font=('Arial', 12))
var7.set("P                             ")
l7.pack()

var8 = tk.StringVar()
l8 = tk.Label(root, textvariable=var8, font=('Arial', 12))
var8.set("N                             ")
l8.pack()

root.mainloop()

