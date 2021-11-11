# -*- coding: utf-8 -*-
"""
Created on Mon Mar 15 20:17:14 2021

@author: stacy_w
"""
import csv
from langdetect import detect
from langdetect.lang_detect_exception import LangDetectException

c = open("2_GameUserReviewDataList_onlyen.csv",'w',encoding="utf8",newline='',errors='ignore')
c2 = open("2_GameUserReviewDataList_noneen.csv",'w',encoding="utf8",newline='',errors='ignore')
writer = csv.writer(c)
writer2 = csv.writer(c2)
writer.writerow(['Game_title','Platform','User_score','User_reviews'])
writer2.writerow(['Game_title','Platform','User_score','User_reviews','Language'])

finderrordtata = 0

with open('1_GameUserReviewDataList.csv', newline='',encoding="utf8", errors='ignore') as csvfile:

    rows = csv.DictReader(csvfile)
    
    for row in rows:
        text = row['User_reviews'].replace('\n', ' ').replace('\r', ' ').strip()
        finderrordtata += 1
        try:
            language = detect(text)
            if language == 'en':
                writer.writerow([row['Game_title'],row['Platform'],row['User_score'],text])
            else:
                writer2.writerow([row['Game_title'],row['Platform'],row['User_score'],text,language])
        except LangDetectException:
            print(finderrordtata)
            pass
            
c.close()
c2.close()
