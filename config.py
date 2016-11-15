from telebot import types

TOKEN = "173564814:AAGa7wka0WesdgCGxLuszv4FHp8vNtC-e08"

commands = {  # command description used in the "help" command
              'start': 'Вы добавлены',
              'help': 'Возможности',
              'make': 'собрать и запустить',
              'plot': 'построить графики и получить себе'
}



optionSelect = types.ReplyKeyboardMarkup(one_time_keyboard=False)  #buttons
hideBoard = types.ReplyKeyboardHide()
