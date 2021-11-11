# -*- coding: utf-8 -*-
"""
Created on Wed Sep 29 19:26:55 2021

@author: stacy_w
"""
import csv

#c = open("5_Test_binary_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("5_Test_absolute_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("5_Test_relative_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("5_Test_none_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')

#c = open("5_Train_binary_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("5_Train_absolute_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("5_Train_relative_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')
c = open("5_Train_ none_allinone.csv",'w',encoding="utf8",newline='',errors='ignore')

writer = csv.writer(c)
writer.writerow(['User_reviews'])

#with open('4_TestUserReview_binary_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
#with open('4_TestUserReview_absolute_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
#with open('4_TestUserReview_relative_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:

with open('4_TrainUserReview_binary_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
#with open('4_TrainUserReview_absolute_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
#with open('4_TrainUserReview_relative_label.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
    
    rows = csv.DictReader(csvfile)
    for row in rows:
        #aspects = 'User_score '+row['User_score']+' points '+row['aspects'].strip()
        review = row['User_reviews'].strip()
        #writer.writerow([aspects+'<sep>'+review])
        writer.writerow([review])#none
        
c.close()
