from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)
		desc.config(text=str(forecast_j["description"]))
		weather.config(text=str(forecast_j["temp"]) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", reload_data)

zheltiy = "#ffb84d"
beliy = "#ffffff"
_w = 100
_h = 30

top_frame = Frame(root, bg=zheltiy, width=_w, height=_h)
middle_frame = Frame(root, bg=beliy,  width=_w, height=_h*3)
bottom_frame = Frame(root, bg=zheltiy, width=_w, height=_h)

top_frame.pack(side=TOP, fill=X)
middle_frame.pack(expand=True, fill=BOTH)
bottom_frame.pack(side=BOTTOM, fill=X)

city = Label(top_frame, font=("Calibri Bold", 12), text="Симферополь", bg=zheltiy)
weather = Label(middle_frame, font=("Impact", 48), bg=beliy)
desc = Label(top_frame, font=("Calibri", 12), bg=zheltiy)


city.pack(pady=0)
weather.pack(expand=True)
desc.pack(pady=0)


reload_data()
root.mainloop()