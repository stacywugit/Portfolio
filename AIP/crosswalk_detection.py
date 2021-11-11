import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
import imghdr
import os
from darkflow.net.build import TFNet
import numpy as np
import cv2

class Window(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)

        menu = tk.Menu(self.master)
        master.config(menu=menu)

        file_menu = tk.Menu(menu)
        file_menu.add_command(label="Read", command=self.openFile)
        menu.add_cascade(label="File", menu=file_menu)
        
        analyze_menu = tk.Menu(menu)        
        analyze_menu.add_command(label="crosswalk", command=self.crosswalk)
        menu.add_cascade(label="Analyze", menu=analyze_menu)

        self.canvas = tk.Canvas(self)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.image1 = None # none yet
        self.image2 = None # none yet

    #Where I open my file
    def openFile(self):
        self.filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select Image File", filetypes=[("JPG Files","*.jpg"),("BMP Files","*.bmp"),("PPM Files","*.ppm")])
        if not self.filename:
            return # user cancelled; stop this method

        self.load = Image.open(self.filename)
        self.origload = self.load
        w, h = self.load.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=350 or h >=350) and (h >= w)):
            self.load = self.load.resize((int(350*ratio2), 350), Image.ANTIALIAS)
        elif ((w >=350 or h >=350) and (h < w)):
            self.load = self.load.resize((350, int(350*ratio1)), Image.ANTIALIAS)
        self.render = ImageTk.PhotoImage(self.load) #must keep a reference to this

        if self.image1 is not None: # if an image was already loaded
            self.canvas.delete(self.image1) # remove the previous image

        self.image1 = self.canvas.create_image((0,200), anchor='w', image=self.render)
        
    def crosswalk(self):
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image
        
        self.newFileName = self.filename
        
        options = {
            'model': 'model.cfg',
            'load': -1,
            'threshold': 0.1,
            'backup':'ckpt/'
        }
        tfnet = TFNet(options)
        original_img = cv2.imread(self.filename)
        original_img = cv2.cvtColor(original_img, cv2.COLOR_BGR2RGB)
        results = tfnet.return_predict(original_img)
        
        newImage = np.copy(self.origload)
        if len(results)!=0:
            for result in results:
                top_x = result['topleft']['x']
                top_y = result['topleft']['y']

                btm_x = result['bottomright']['x']
                btm_y = result['bottomright']['y']

                confidence = result['confidence']
                label = result['label'] + " " + str(round(confidence, 2))

            if confidence > 0.1:
                newImage = cv2.putText(newImage, label, (top_x, top_y-5), cv2.FONT_HERSHEY_SIMPLEX ,1, (0, 255, 0), 1, cv2.LINE_AA)
                newImage = cv2.rectangle(newImage, (top_x, top_y), (btm_x, btm_y), (255,0,0), 3)

            cv2.imwrite('output.jpg', cv2.cvtColor(newImage, cv2.COLOR_RGB2BGR))

        else:
            cv2.imwrite('output.jpg', cv2.cvtColor(newImage, cv2.COLOR_RGB2BGR))

        self.load2 = Image.open('output.jpg')
        w, h = self.load2.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=350 or h >=350) and (h >= w)):
            self.load2 = self.load2.resize((int(350*ratio2), 350), Image.ANTIALIAS)
        elif ((w >=350 or h >=350) and (h < w)):
            self.load2 = self.load2.resize((350, int(350*ratio1)), Image.ANTIALIAS)
        self.render2 = ImageTk.PhotoImage(self.load2) #must keep a reference to this

        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image

        self.image2 = self.canvas.create_image((360,200), anchor='w', image=self.render2)
        

root = tk.Tk()
root.geometry("%dx%d" % (710, 400))
root.title("FP")
app = Window(root)
app.pack(fill=tk.BOTH, expand=1)
root.mainloop()