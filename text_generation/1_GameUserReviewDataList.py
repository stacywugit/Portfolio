# -*- coding: utf-8 -*-
"""
Created on Tue Nov 10 12:47:57 2020

@author: 60747045S
"""
from bs4 import BeautifulSoup
from urllib.request import urlopen, Request
import csv
import time

def sleeptime(hour,min,sec):
    return hour*3600 + min*60 + sec;

tStart = time.time()#計時開始
#c = open("GameUserReviewDataList.csv",'w',encoding='utf-8',newline='')
c = open("1_GameUserReviewDataList.csv",'a',encoding='utf-8',newline='')
writer = csv.writer(c)
#writer.writerow(['Game_title','Platform','User_score','User_reviews'])

urllist = ["https://www.metacritic.com/game/pc/tom-clancys-the-division-2/user-reviews"]

agent = 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_3) AppleWebKit/537.36\
(KHTML, like Gecko) Chrome/35.0.1916.47 Safari/537.36'
#i = 0
i = 0
while(i<1):
    request = Request(urllist[i], headers= {'User-Agent' : agent})
    while(request):
        html = urlopen(request).read().decode()
        soup = BeautifulSoup(html, "html.parser")
        content = ['0']*4
        title = soup.find('a',class_='hover_none')
        title = title.text.strip()
        content[0] = title
        platform = soup.find('span',class_='platform')
        platform = platform.text.strip()
        content[1] = platform
        all_crtics_reviews = soup.find('ol',class_='reviews user_reviews')
        review_sections = all_crtics_reviews.find_all('div',class_='review_section')
        for reviews in review_sections:
            score = reviews.find('div',class_='review_grade')
            if score:
                score = score.text.strip()
                content[2] = score
                review = reviews.find('div',class_='review_body')
                if(review.find('span',class_='inline_expand_collapse inline_collapsed')):
                    review = review.find('span',class_ = 'blurb blurb_expanded')
                    
                review = review.text.replace('\n', ' ').replace('\r', ' ').strip()
                content[3] = review
                templist = []
                templist.append(content[0])
                templist.append(content[1])
                templist.append(content[2])
                templist.append(content[3])
                writer.writerow(templist)
                time.sleep(sleeptime(0,0,5))
                
        pages = soup.find('div',class_='page_nav')
        next_page = pages.find('span',class_='flipper next')
        next_page = next_page.find('a',class_='action')
        if(next_page):
            next_page = next_page.get('href')
            next_page = 'https://www.metacritic.com' + next_page
            print(next_page)
            request = Request(next_page, headers= {'User-Agent' : agent})                    
            time.sleep(sleeptime(0,0,30))
        else:
            request = None
    
    time.sleep(sleeptime(0,1,0))
    i += 1            
    
tEnd = time.time()#計時結束
c.close()
print ("It cost %f sec" % (tEnd - tStart))