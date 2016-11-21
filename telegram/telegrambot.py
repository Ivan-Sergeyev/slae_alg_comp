#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import config
import sys
from config import commandss
from config import optionSelect
from config import hideBoard
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
admin_list = dict()
admin_list[273084068] = 1 #Ivan
admin_list[73972270] = 1
knownUsers = []
newUsers = 0
userStep = {}
userList = pd.DataFrame()

allPhoto = []
photoUserCurrent = {}

import commands, os, string


def listener(messages):
    """
    When new messages arrive TeleBot will call this function.
    """
    for m in messages:
        if m.content_type == 'text':
            # print the sent message to the console
            print (" [" + str(m.chat.id) + "]: " + m.text)
       
bot = telebot.TeleBot(config.TOKEN)
bot.set_update_listener(listener)  # register listener


@bot.message_handler(commands=["start", 'старт', 'Старт'])
def comm_start(message):
    cid = message.chat.id
    print cid
    if (admin_list[cid]):
        global newUsers
        global userStep

        newUsers += 1
        userStep[cid] = 1
        knownUsers.append(cid)
        bot.send_message(cid, "Я вас слушаю")#, reply_markup=optionSelect)
        comm_help(message)
    else:
        bot.send_message(cid, "Добро пожаловать")#, reply_markup=optionSelect)


@bot.message_handler(commands=['help', 'помощь', 'Помощь'])
def comm_help(message):
    cid = message.chat.id
    if (admin_list[cid]):
        help_text = "И - инстукция: \n"
        for key in commandss:  # generate help text out of the commands dictionary defined at the top
            help_text += "/" + key + ": "
            help_text += commandss[key] + "\n"
        bot.send_message(cid, help_text)  # send the generated help page


@bot.message_handler(commands=['plot'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        a = sb.Popen(['make', 'plot'])
        bot.send_message(cid, "Ok")

@bot.message_handler(commands=['pull'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        a = sb.Popen(['git', 'pull'])
        bot.send_message(cid, "Ok")


indicate = 0
@bot.message_handler(commands =['kill'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        output = commands.getoutput("ps -f|grep main")
        proginfo = output.split("\n")
        if (len(proginfo)==1):  bot.send_message(cid, "Nothing to kill")    
        else:
            a = sb.Popen(['killall', 'main'])
            bot.send_message(cid, "Killall main")    


@bot.message_handler(commands=['graph'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        photo = open('temp_graphs/All Methods.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Gauss Method Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Jacobi Method Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Overrelaxation Method with tau=0.500000 Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Overrelaxation Method with tau=1.250000 Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Overrelaxation Method with tau=1.500000 Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Overrelaxation Method with tau=1.750000 Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/all/Seidel Method Full.png', 'rb')
        bot.send_photo(cid, photo)
        photo = open('temp_graphs/Overrelaxation Methods.png', 'rb')
        bot.send_photo(cid, photo)
        bot.send_message(cid, "Everything is ok")

@bot.message_handler(commands=['make'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        output = commands.getoutput("ls -f|grep main")
        proginfo = string.split(output)
        a = dict()
        a['main'] = 0
        for i in range(len(proginfo)):
            a[proginfo[i]] = 1;
        if (a['main']): sb.Popen(['rm', 'main'])
        # kill old process
        output = commands.getoutput("ps -f|grep main")
        proginfo = output.split("\n")
        if (len(proginfo) > 2 ):  bot.send_message(cid, "Old process already start, kill them use \kill") 
        else: 
            sb.Popen(['make'])
            bot.send_message(cid, "Program start")

@bot.message_handler(commands=['status'])
def maker(message):
    cid = message.chat.id
    if (admin_list[cid]):
        output = "status"
        term = pd.read_csv(".progress_small", header = None, sep = ' ')
        if (term.shape[1] == 1): output = "small test: done\n"
        else: output = "small test: size = " + str(term[0].values[0]) + ", mu = " + str(term[1].values[0]) + ", effort = " + str(term[2].values[0])+ "\n"
        
        term = pd.read_csv(".progress_large", header = None, sep = ' ')
        if (term.shape[1] == 1): output += "large test: done\n"
        else: output += "large test: size = " + str(term[0].values[0]) + ", mu = " + str(term[1].values[0]) + ", effort = " + str(term[2].values[0])+ "\n"
    

       #check process in ps
        outcom = commands.getoutput("ps -f|grep main")
        proginfo = outcom.split("\n")
        if (len(proginfo) > 2 ):  output += "process have work yet\n"
        else:  output += "process don't work\n"

        output += "cat log.txt: \n\n"+commands.getoutput("tail -n 10 log.txt")


        
        bot.send_message(cid, output) 
        
bot.polling()

