from tkinter import *
import json
import requests

def site(event=None):
	try:
		upload = requests.get('http://localhost:3000/raw').content.decode("utf8")
		upload_date = json.loads(upload)

		up1.config(text=str(upload_date["description"]))
		main.config(text=str(round(upload_date["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.pack_propagate(0)
root.bind("<Button-1>", site)
tex = "Симферополь"
root.geometry("200x250")

yellow = "#ffa343"
f = 100
h = 30

up_frame =    Frame(root, bg= yellow, width=f, height=h)
main_frame = Frame(root, bg="white",  width=f, height=h*3)
down_frame = Frame(root, bg=yellow, width=f, height=h)

up_frame.pack(side=TOP, fill=X)
main_frame.pack(expand=True, fill=BOTH)
down_frame.pack(side=BOTTOM, fill=X)

up = Label(up_frame, font=("Arial", 14), text= tex, bg=yellow)
main = Label(main_frame, font=("Calibri", 52), bg="white")
up1 = Label(up_frame, font=("Arial", 14), bg=yellow)


up.pack(pady=0)
main.pack(expand=True)
up1.pack(pady=0)


site()
root.mainloop()