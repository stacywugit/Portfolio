# -*- coding: utf-8 -*-
"""
Created on Sun Oct 10 11:19:08 2021

@author: stacy_w
"""

import pandas as pd

reviews = pd.read_csv('2_GameUserReviewDataList_onlyen.csv')

df = reviews

df = df[df['User_reviews'].apply(lambda x: len(x) < 900)]

test_set = df.sample(n = 100)
df = df.loc[~df.index.isin(test_set.index)]

test_set.to_csv('testureview.csv')
df.to_csv('trainureview.csv')
