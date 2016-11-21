from telebot import types

TOKEN = "173564814:AAGa7wka0WesdgCGxLuszv4FHp8vNtC-e08"

commandss = {  # command description used in the "help" command
              'start': 'Вы добавлены',
              'help': 'Возможности',
              'make': 'собрать и запустить',
              'plot': 'построить графики',
              'graph': 'получить графики (необходимо подождать после plot)',
              'kill': 'завершить запущенную программу',
              'pull': 'получить новую версию с github',
              'status': 'получить последние 10 строк из log_err'
}



optionSelect = types.ReplyKeyboardMarkup(one_time_keyboard=False)  #buttons
hideBoard = types.ReplyKeyboardHide()
