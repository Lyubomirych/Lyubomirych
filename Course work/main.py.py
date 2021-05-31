import pygame
import random
import sys
from checkers.constants import WIDTH, HEIGHT, SQUARE_SIZE, GREY, TREE
from checkers.game import Game
from tkinter import *
from tkinter import messagebox
import requests
import time

pygame.init()
pygame.font.init()

FPS = 60

WIN = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Шашки - Курсач')

def screen_to_world(pos):
    x, y = pos
    row = y // SQUARE_SIZE
    col = x // SQUARE_SIZE
    return row, col

def randomize(gamer_1, gamer_2): #кто ходит первый?
    first = random.randint(0,1)
    if first == 0:
        Tk().wm_withdraw() 
        messagebox.showinfo("Рулетка решила, что", "Красными играет: " +
                gamer_1.get() + " Белыми играет: " + gamer_2.get())
        #Первый ходит первый игрок
    else:
        Tk().wm_withdraw() 
        messagebox.showinfo("Рулетка решила, что", "Красными играет: " +
                gamer_2.get() + "\n Белыми играет: " + gamer_1.get())
        #Первый ходит второй игрок

def data_entry(): #Ввод имен для рандома
    root = Tk()
    root.title("Рандом игроков")
    gamer_1 = StringVar()
    gamer_2 = StringVar()
    gamer_1_label = Label(text="Введите игрока 1:")
    gamer_2_label = Label(text="Введите игрока 2:")
    gamer_1_label.grid(row=0, column=0, sticky="w")
    gamer_2_label.grid(row=1, column=0, sticky="w")
    gamer_1_entry = Entry(textvariable=gamer_1)
    gamer_2_entry = Entry(textvariable=gamer_2)
    gamer_1_entry.grid(row=0,column=1, padx=5, pady=5)
    gamer_2_entry.grid(row=1,column=1, padx=5, pady=5)

    root.destroy
    root.mainloop()    
    randomize(gamer_1, gamer_2) #вызываем рандом
    

def drawing(winner):    #Окно победителя и надпись о перезапуске
    draw = True
    while draw:
        for event in pygame.event.get():
           if event.type == pygame.QUIT:
               draw = False
           elif event.type == pygame.KEYDOWN:
               if event.key == pygame.K_r:
                   main()
        sc = pygame.display.set_mode((WIDTH, HEIGHT))
        sc.fill(TREE)
        f1 = pygame.font.Font(None, 36)
        text1 = f1.render(" Победа " + winner  , True,
                          (180, 0, 0))
        text2 = f1.render("Для перезапуска нажмите R ", True,
                          (180, 0, 0))

        sc.blit(text1, (10, 50))
        sc.blit(text2, (200, 200))
        pygame.display.update()

server_address: str
session: str
player_id: int
my_turn: bool

def is_my_turn():
    global player_id, my_turn, server_address, session
    # возвращает True, если клиент в режиме ожидания, иначе False
    return my_turn

def send_move(move):
    global player_id, my_turn, server_address, session
    # ничего не возвращает. Отправляет ход на сервер
    data = {
        'move': move,
        'player': player_id,
        'uid': session
    }
    requests.post(server_address, json = data)

def set_my_turn(status):
    global player_id, my_turn, server_address, session
    if (type(status) == bool):
        my_turn = status

def get_data_from_server():
    global player_id, my_turn, server_address, session
    # возвращает (int, boolean): номер игрока и ходит ли этот игрок первым
    p = { 'uid': session }
    response = requests.get(server_address, params = p)
    j = response.json()
    status = j['status']
    if status == 'assign-role':
        my_turn = j['your-turn']
        player_id = j['player']
        return player_id, my_turn
    elif status == 'full':
        print('GAME IS FULL YOU CANNOT CONNECT')
        exit()
    else:
        print('UNKNOWN STATUS', status, 'IN GET_DATA_FROM_SERVER! PANIC')
        exit()

class ServerEvent:
    def __init__(self, no_moves = False, timeout = False, move = None):
        self.no_moves = no_moves
        self.timeout = timeout
        self.move = move

    def is_no_moves(self):
        return self.no_moves

    def is_timeout(self):
        return self.timeout

    def is_move(self):
        return self.move != None

    def get_move(self):
        return self.move

def get_other_connected():
    global server_address, session, player_id
    p = { 'uid': session, 'player': player_id }
    response = requests.get(server_address + "other_connected", params = p)
    j = response.json()
    print(j)
    return j["other-connected"]

def get_event_from_server():
    global player_id, my_turn, server_address, session
    p = {
        'uid': session,
        'player': player_id
    }
    response = requests.get(server_address, params = p)
    j = response.json()
    status = j['status']
    if status == 'no-moves' or status == 'empty':
        return ServerEvent(no_moves = True)
    elif status == 'move':
        return ServerEvent(move = j['move'])
    elif status == 'timeout':
        return ServerEvent(timeout = True)
    else:
        print('PANIC ERROR UNKNOWN STATUS', status)
        exit()

def main():
    global player_id, my_turn, server_address, session
    run = True
    clock = pygame.time.Clock()
    game = Game(WIN)
    while run:
        clock.tick(FPS)

        if game.winner() != None:
            print(game.winner())
            run = False

        if not my_turn:
            server_event = get_event_from_server()

            if server_event.is_move():
                move = server_event.get_move()
                print(move)

                colon = move.index(':')
                from_move = move[0:colon]
                to_move = move[colon+1:]

                dot = from_move.index('.')
                from_row, from_col = from_move[0:dot], from_move[dot+1:]
                dot = to_move.index('.')
                to_row, to_col = to_move[0:dot], to_move[dot+1:]

                game.select(int(from_row), int(from_col))
                game.select(int(to_row), int(to_col))

                my_turn = True

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False

            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_r:
                    main()
            
            if my_turn and event.type == pygame.MOUSEBUTTONDOWN:
                pos = pygame.mouse.get_pos()
                row, col = screen_to_world(pos)
                if game.select(row, col)[1]:
                    send_move(f'{prev_row}.{prev_col}:{row}.{col}')
                    my_turn = False

                prev_row, prev_col = row, col
        
        game.update()

    if game.winner() == (166, 20, 0):
        drawing('Красных')
    elif game.winner() == (255, 255, 255):
        drawing('Белых')
    else: drawing('никому не досталась!')
    run = False
    pygame.quit()

server_address = 'http://localhost:8080/'
session = 'e'
get_data_from_server()
while not get_other_connected():
    time.sleep(1);
    print('other not connected')
print(server_address, session, player_id, my_turn)

data_entry()
main()
