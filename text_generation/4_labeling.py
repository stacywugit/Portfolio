# -*- coding: utf-8 -*-
"""
Created on Sun Apr 11 21:02:36 2021

@author: stacy_w
"""
import csv
from nltk.stem import PorterStemmer
from nltk.tokenize import RegexpTokenizer

#c = open("4_TestUserReview_binary_label.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("4_TestUserReview_absolute_label.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("4_TestUserReview_relative_label.csv",'w',encoding="utf8",newline='',errors='ignore')

#c = open("4_TrainUserReview_binary_label.csv",'w',encoding="utf8",newline='',errors='ignore')
#c = open("4_TrainUserReview_absolute_label.csv",'w',encoding="utf8",newline='',errors='ignore')
c = open("4_TrainUserReview_relative_label.csv",'w',encoding="utf8",newline='',errors='ignore')

writer = csv.writer(c)
writer.writerow(['Game_title','Platform','User_score','User_reviews','aspects'])
stemmer = PorterStemmer()

Graphics = ['graphic', 'art', 'visual', 'aesthetic', 'animation', 'fidelity', 'environment',
            'scenery', 'motion', 'map', 'landscape', 'texture', 'surroundings', 'background']
Gameplay = ['missions', 'quests', 'objectives', 'tasks', 'activities', 'reward', 'item', 'gun',
            'inventory', 'weapon', 'system', 'mode', 'combat', 'gameplay', 'mechanic',
            'experience', 'boss', 'enemies', 'villains', 'baddies', 'fights', 'interface', 'UI',
            'pve', 'pvp', 'customize', 'playstyle' , 'immersion', 'explore', 'loot', 'actions',
            'roles', 'balance', 'puzzles', 'microtransactions', 'micro transactions',
            'battle', 'sidequests', 'minigames', 'stealth', 'nostalgia', 'dungeon', 'tutorial',
            'monster', 'avatar', 'strategic', 'chores', 'vehicle', 'raid', 'armor', 'replayability',
            'VR', 'AI', 'melee', 'micro-transactions', 'gacha', 'antagonist']
Audio = ['audio', 'sound', 'music', 'soundtrack', 'melody', 'voice acting']
Story = ['plot', 'story', 'storyline', 'dialogue', 'ending', 'character', 'cast', 'NPC',
         'protagonist', 'chapter', 'atmosphere', 'storytelling', 'script, emotion',
         'flashback', 'cut scenes', 'conversations', 'backstory', 'lore']
Community = ['community', 'toxic', 'campers', 'cheaters']
Social = ['multiplayer', 'friends']
Technical = ['technical', 'performance', 'physics', 'server', 'bug', 'connection', 'lag', 'clunky',
             'latency', 'ping', 'crash', 'glitch', 'stuck', 'flicker', 'patch', 'hardware', 'online',
             'offline', 'error', 'console', 'accessibility', 'frame rate', 'camera', 'optimization',
             'resolution', 'CPUs', 'mouse', 'loading']
Value = ['money', 'cash', 'dollar', 'price', 'DLC', 'purchase', 'buy', 'penny', 'refund']
Market = ['trailer', 'expectations', 'prequel', 'sequel', 'predecessor', 'advertised',
          'media', 'journalists', 'propaganda', 'company', 'franchise', 'leak', 'pander',
          'creators' , 'remake', 'series', 'expansion']
Others = ['LGBT', 'SJW', 'industry', 'message', 'agenda', 'politic', 'feminism', 'realism',
          'realistic', 'culture', 'gay', 'lesbian', 'transgender', 'sexuality', 'controversial',
          'violence', 'atrocity', 'ideological', 'democracy', 'Russophobia', 'stereotype',
          'war crime', 'terrorist', 'fascism', 'innovation', 'traditional', 'Russia', 'racist',
          'America', 'bisexual', 'Asian', 'country', 'discrimination', 'Mongols', 'bandwagon']
General = ['game', 'content']#+Game_title

Aspects = [Graphics, Gameplay, Audio, Story, Community, Social, Technical, Value, Market, Others, General]
for i, aspect in enumerate(Aspects):
    for j, term in enumerate(aspect):
        Aspects[i][j] = term.replace(term, stemmer.stem(term))

#with open('3_TestUserReview.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
with open('3_TrainUserReview.csv', newline='',encoding="utf8", errors='ignore') as csvfile:
    rows = csv.DictReader(csvfile)
    for row in rows:
        text = row['User_reviews']
        tokenizer = RegexpTokenizer(r'\w+')
        tokenized_review = tokenizer.tokenize(text)
        stemmed_review = ""
        word_counts = 0#relative
        for words in tokenized_review:
            word_counts = word_counts + 1#relative
            stemmed_review = stemmed_review + " " + stemmer.stem(words)
        
        aspter_term_count = [0,0,0,0,0,0,0,0,0,0,0]
        for i, aspect in enumerate(Aspects):
            for j, term in enumerate(aspect):
                term = ' ' + term + ' '
                if term in stemmed_review:
                    aspter_term_count[i] = aspter_term_count[i] + 1#absolute
                    #aspter_term_count[i] = 1#binary
                    
        #game name as general aspect
        game_name_text = row['Game_title']
        tokenized_game_name = tokenizer.tokenize(game_name_text)
        stemmed_game_name = ""
        for words in tokenized_game_name:
            stemmed_game_name = stemmed_game_name + " " + stemmer.stem(words)
        stemmed_game_name = stemmed_game_name + " "
        if stemmed_game_name in stemmed_review:
            aspter_term_count[10] = aspter_term_count[10] + 1#absolute
            #aspter_term_count[10] = 1#binary
        
        aspect_text = ''
        
        for i in range(11):
            if aspter_term_count[i]:
                if i == 0:
                    aspect_text = aspect_text + '#Graphics'
                elif i == 1:
                    aspect_text = aspect_text + ' #Gameplay'
                elif i == 2:
                    aspect_text = aspect_text + ' #Audio'
                elif i == 3:
                    aspect_text = aspect_text + ' #Story'
                elif i == 4:
                    aspect_text = aspect_text + ' #Community'
                elif i == 5:
                    aspect_text = aspect_text + ' #Social'
                elif i == 6:
                    aspect_text = aspect_text + ' #Technical'   
                elif i == 7:
                    aspect_text = aspect_text + ' #Value'
                elif i == 8:
                    aspect_text = aspect_text + ' #Market'
                elif i == 9:
                    aspect_text = aspect_text + ' #Others'
                else:
                    aspect_text = aspect_text + ' #General'
                aspect_percentage = round(aspter_term_count[i] / word_counts * 100, 5)#relative
                aspect_text = aspect_text + ' ' + str(aspect_percentage) +' percentage '
                #aspect_text = aspect_text + ' ' + str(aspter_term_count[i]) +' times '#absolute
                        
        writer.writerow([row['Game_title'],row['Platform'],row['User_score'], row['User_reviews'], aspect_text.strip()])
            
                    
        
c.close()
