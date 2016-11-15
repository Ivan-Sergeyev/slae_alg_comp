#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import config
import sys
from config import commands
from config import optionSelect
from config import hideBoard
#from config import room_list, alco_quest, slogans, tosts, girls_connect, boys_connect
#from config import MASS_MAIL_KEY
import telebot
import logging

import numpy as np
import pandas as pd
import random
import re
import pickle


import subprocess as sb

from telebot import types

user_list = pd.DataFrame()
knownUsers = []
newUsers = 0
userStep = {}
userList = pd.DataFrame()

allPhoto = []
photoUserCurrent = {}

# class Photo():
#     def __init__(self, file_id):
#         self.voted_user = []
#         self.rate = 0
#         self.file_id = file_id

# # allPhotoRate = {1: PhotoRate}


def init():
    global userList
    global user_list
    global allPhoto

    userList = pd.read_csv(r'user_list.csv', index_col='index')
    #allPhoto = pickle.load(open('photos.txt', 'rb'))
    for i in range(1, userList.knownUsers.size + 1):
         uid = int(userList.knownUsers.get(i))
         knownUsers.append(uid)
         userStep[uid] = int(userList.userStep.get(i))
    print (userList)
    user_list = userList
    user_list.columns = ['uid', 'step']




def shut_up():
    global userList

    print ('new user number = ', newUsers, '\n')
    print (userList)
    print (knownUsers)
    print (userStep)

    for i in range(0, newUsers):
        uid = knownUsers[userList.knownUsers.size + i]
        step = userStep[uid]
        userList = userList.append(pandas.DataFrame([[uid, step]], columns=['knownUsers', 'userStep'], index=[userList.knownUsers.size + i + 1]))

    print (userList)

    userList.to_csv(r'user_list.csv')
    sys.exit(0)


def get_user_step(uid):
    if uid in userStep:
        return userStep[uid]
    else:
        knownUsers.append(uid)
        userStep[uid] = 0
        print ("New user detected, who hasn't used \"/start\" yet")
        return 0


def update_user_info(uid, info = None):
    global user_list
    user = user_list.loc[user_list['uid'] == uid]
    if user.empty:
        user_list = user_list.append({'uid':uid}, ignore_index = True)
        user = user_list.loc[user_list['uid'] == uid]
    if info:
        for x in info.keys():
            user_list[x][user.index.values[0]] = info[x]

    print(user_list)





def listener(messages):
    """
    When new messages arrive TeleBot will call this function.
    """
    for m in messages:
        if m.content_type == 'text':
            # print the sent message to the console
            print (" [" + str(m.chat.id) + "]: " + m.text)
        # if m.content_type == 'photo':
        #     # print(m.photo[0])
        #     # bot.send_photo(cid, m.photo[1].file_id)
        #     # TODO Don't append same photo
        #     global allPhoto
        #     allPhoto.append(Photo(m.photo[0].file_id))
        #     #with open("photos.txt", "a") as myfile:
        #     #    myfile.write("m.photo[0].file_id")
        #     pickle.dump(allPhoto, open('photos.txt', 'wb'))

bot = telebot.TeleBot(config.TOKEN)
bot.set_update_listener(listener)  # register listener


@bot.message_handler(commands=["start", 'старт', 'Старт'])
def comm_start(message):
    cid = message.chat.id
    if cid not in knownUsers:
        global newUsers
        global userStep

        newUsers += 1
        userStep[cid] = 1
        knownUsers.append(cid)
        bot.send_message(cid, "Программа запущена")#, reply_markup=optionSelect)
        comm_help(message)
    else:
        bot.send_message(cid, "Добро пожаловать")#, reply_markup=optionSelect)
        userStep[cid] = 1


@bot.message_handler(commands=['shutUp'])
def comm_shutUp(message):
    cid = message.chat.id
    bot.send_message(cid, 'Ок')
    shut_up()


@bot.message_handler(commands=['help', 'помощь', 'Помощь'])
def comm_help(message):
    cid = message.chat.id
    help_text = "И - инстукция: \n"
    for key in commands:  # generate help text out of the commands dictionary defined at the top
        help_text += "/" + key + ": "
        help_text += commands[key] + "\n"
    bot.send_message(cid, help_text)  # send the generated help page


@bot.message_handler(commands=['plot'])
def maker(message):
    cid = message.chat.id
    a = sb.Popen(['make', 'plot'])
    bot.send_message(cid, "Ok")


@bot.message_handler(commands=['graph'])
def maker(message):
    cid = message.chat.id
    photo = open('graph_python/Gauss MethodTime(size of matrix).png', 'rb')
    bot.send_photo(cid, photo)
    photo = open('graph_python/All Method.png', 'rb')
    bot.send_photo(cid, photo)
    photo = open('graph_python/Jacobi MethodTime(size of matrix).png', 'rb')
    bot.send_photo(cid, photo)
    photo = open('graph_python/Overrelaxation Method with tau=0.500000Time(size of matrix).png', 'rb')
    bot.send_photo(cid, photo)
    photo = open('graph_python/Overrelaxation Method with tau=1.500000Time(size of matrix).png', 'rb')
    bot.send_photo(cid, photo)
    photo = open('graph_python/Seidel MethodTime(size of matrix).png', 'rb')
    bot.send_photo(cid, photo)
    bot.send_message(cid, "Everything is ok")

@bot.message_handler(commands=['make'])
def maker(message):
    cid = message.chat.id
    #sb.Popen('rm main')
    sb.Popen(['make'])
    bot.send_message(cid, "ok")
# #--------------------
# def _create_choices_button_for_photo():
#     markup = types.ReplyKeyboardMarkup()
#     itembtn1 = types.KeyboardButton('Like')
#     itembtn2 = types.KeyboardButton('Dislike')
#     markup.row(itembtn1, itembtn2)
#     return markup


# @bot.message_handler(commands=['photo', 'фото', 'Фото'])
# def photo(message):
#     global photoUserCurrent
#     global allPhoto

#     cid = message.chat.id
#     if len(allPhoto) == 0:
#         bot.send_message(cid, "Ещё нет фото для голосования")
#         return

#     uid = message.from_user.id

#     no_vote_photo = []
#     for i, photo in enumerate(allPhoto):
#         if not uid in photo.voted_user:
#             no_vote_photo.append(i)

#     if len(no_vote_photo) == 0:
#         list_number = random.sample(range(0, len(allPhoto)), min(3, len(allPhoto)))
#         # photo = allPhoto[random.randint(0, len(allPhoto) - 1)]
#         for number in list_number:
#             bot.send_photo(cid, allPhoto[number].file_id)
#         # bot.send_message(cid, "Пока ещё нет фото доступных для голосования\nПосмотрите на несколько случайных, раположенных выше")
#         return

#     number = no_vote_photo[random.randint(0, len(no_vote_photo) - 1)]

#     photoUserCurrent[message.from_user.id] = number
#     photoCurrent = photoUserCurrent[message.from_user.id]
#     photo = allPhoto[photoCurrent]


#     markup = _create_choices_button_for_photo()
#     bot.send_photo(cid, photo.file_id, reply_markup=markup, caption="Оцените")
#     markup = types.ReplyKeyboardHide(selective=False)

# @bot.message_handler(commands=['rating', 'рейтинг', 'Рейтинг'])
# def photo_rate(message):
#     cid = message.chat.id
#     # Just in case
#     markup = types.ReplyKeyboardHide(selective=False)
#     if allPhoto == []:
#         bot.send_message(cid, "Ещё нет фото для голосования",
#                          reply_markup=markup)
#         return

#     mask_photos = []
#     for i, photo in enumerate(allPhoto):
#         mask_photos.append((i, photo))

#     mask_photos.sort(key=lambda x: x[1].rate, reverse=True)
#     len_mask_photos = len(mask_photos)
#     for i in range(4, -1, -1):
#         if i < len_mask_photos:
#             photo = mask_photos[i][1]
#             bot.send_photo(cid, photo.file_id, reply_markup=markup,
#                          caption="Рейтинг: {}".format(photo.rate))

#     # for i, photo in enumerate(allPhoto):
#     #     bot.send_photo(cid, photo.file_id, reply_markup=markup,
#     #                    caption="Номер фото:{}\nРейтинг: {}".\
#     #                    format(i, photo.rate))


# @bot.message_handler(func=lambda message: True)
# def vote_photo(message):
#     global allPhoto
#     global photoUserCurrent
#     print(photoUserCurrent)
#     photoCurrent = photoUserCurrent.get(message.from_user.id, -1)
#     print(photoCurrent)
#     if 0 <= photoCurrent < len(allPhoto):
#         cid = message.chat.id
#         uid = message.from_user.id
#         photo = allPhoto[photoCurrent]
#         markup = types.ReplyKeyboardHide(selective=False)
# 	# if uid in photo.voted_user:
# 	#     # TODO
# 	#     bot.send_message(cid, "Вы уже голосовали",
# 	#     		     reply_markup=markup)
# 	#     return
#         if message.text in ['Like', 'Dislike']:
#             if uid in photo.voted_user:
#                 bot.send_message(cid, "Вы уже голосовали",
#                                  reply_markup=markup)
#                 return
#             if message.text == 'Like':
#                 photo.rate += 1
#             else:
#                 photo.rate -= 1
#             photo.voted_user.append(uid)
#             pickle.dump(allPhoto, open('photos.txt', 'wb'))


#             bot.send_message(cid, "Ваш голос учтён. Проголосовать ещё: /photo",
#                              reply_markup=markup)
#         # else:
#         #     markup = _create_choices_button_for_photo()
#         #     bot.send_message(cid, "Отправь доступный ответ",
#         #                     reply_markup=markup)
#---------------------------------------------------------------------

#logger = telebot.logger
#telebot.logger.setLevel(logging.DEBUG)

init()
# update_user_info(34)

#for x in knownUsers:
#    bot.send_message(x, 'Тима раков, я ливаю')
bot.polling()




"""
@bot.message_handler(func=lambda message: get_user_step(message.chat.id) == 1)
def comm_optionChoosing(message):
    cid = message.chat.id

    if message.text == 'shutUp':
        bot.send_message(cid, message.text, reply_markup=hideBoard)
        userStep[cid] = 0
        shut_up()
    elif message.text == 'Расписание':
        #optionSelect.add('421', '422', '423')
        bot.send_message(cid, 'Выберите группу', reply_markup=optionSelect)

        userStep[cid] = 2
    else:
        bot.send_message(cid, 'Push one of the buttons, please.')

@bot.message_handler(func=lambda message: get_user_step(message.chat.id) == 2)
def comm_groupSelection(message):
    cid = message.chat.id

    if str(message.text).isdigit():
        grNum = int(message.text)
        print (grNum)
        print (table.current_day())
        print (table.current_hour())
        lesson, start, end = table.current_lesson(grNum)
        print (lesson, start, end)
        if lesson != 'Empty':
            teacher_name = table.teacher(grNum, lesson)[0]
            lesson_info = 'Текущее занятие: ' + lesson + '\n'
            lesson_info+= 'Начало: ' + str(start) + '\n'
            lesson_info+= 'Конец: '+ str(end) + '\n Учитель: ' + teacher_name
            bot.send_message(cid, lesson_info)

            teacher_info = get_teacher_info(teacher_name)
            if teacher_info != '':
                bot.send_message(cid, teacher_info, parse_mode='HTML')

        else:
            bot.send_message(cid, 'У Вас сейчас нет занятий, отдыхайте :)')
        userStep[cid] = 0


    else:
        bot.send_message(cid, 'Пожалуйста, введите корректный номер!')

@bot.message_handler(func=lambda message: rating_by_name(message.text)[0] != None)
def comm_teacherInfo(message):
    cid = message.chat.id
    bot.send_message(cid, get_teacher_info(message.text), parse_mode='HTML')
"""



