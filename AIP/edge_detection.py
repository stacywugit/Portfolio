import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk
from matplotlib import pyplot as plt 
import numpy as np
import pywt
import random
import math
import imghdr
import os

class Window(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)

        menu = tk.Menu(self.master)
        master.config(menu=menu)

        file_menu = tk.Menu(menu)
        file_menu.add_command(label="Read", command=self.openFile)
        menu.add_cascade(label="File", menu=file_menu)
        
        analyze_menu = tk.Menu(menu)        
        analyze_menu.add_command(label="Write", command=self.WriteImage)
        analyze_menu.add_command(label="Hstogram", command=self.Hstogram)
        analyze_menu.add_command(label="0 Mean Gaussian noise", command=self.inputvar)
        analyze_menu.add_command(label="Haar wavelet", command=self.inputlayernum)
        analyze_menu.add_command(label="histogram equalization", command=self.histogramequalization)
        analyze_menu.add_command(label="Convolution", command=self.maskinput)
        menu.add_cascade(label="Analyze", menu=analyze_menu)

        self.canvas = tk.Canvas(self)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.image1 = None # none yet
        self.image2 = None # none yet
        self.image3 = None # none yet
        self.image4 = None # none yet
        self.Label = None
        self.Label2 = None
        self.Label3 = None
        self.varentry = None
        self.varentry2 = None
        self.btn = None
        self.btn2 = None
        self.btn3 = None
        self.maskentry = [None]*9
#--------------------------------open image file and display in gray level----------------------------------
    def openFile(self):
        self.filename = filedialog.askopenfilename(initialdir=os.getcwd(), title="Select Image File", filetypes=[("JPG Files","*.jpg"),("BMP Files","*.bmp"),("PPM Files","*.ppm")])
        if not self.filename:
            return # user cancelled; stop this method

        self.load = Image.open(self.filename).convert('L')
        self.origload = self.load
        w, h = self.load.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=300 or h >=300) and (h >= w)):
            self.load = self.load.resize((int(300*ratio2), 300), Image.ANTIALIAS)
        elif ((w >=300 or h >=300) and (h < w)):
            self.load = self.load.resize((300, int(300*ratio1)), Image.ANTIALIAS)
        self.render = ImageTk.PhotoImage(self.load) #must keep a reference to this

        if self.Label is not None:
            self.Label.destroy()
            self.btn.destroy()
            self.varentry.destroy()
        if self.Label2 is not None:
            self.Label2.destroy()
            self.btn2.destroy()
        if self.Label3 is not None:
            self.Label3.destroy()
            self.btn3.destroy()
            for i in range(9):
                self.maskentry[i].destroy()
        if self.image4 is not None: # if an image was already loaded
            self.canvas.delete(self.image4) # remove the previous image
        if self.image3 is not None: # if an image was already loaded
            self.canvas.delete(self.image3) # remove the previous image
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image
        if self.image1 is not None: # if an image was already loaded
            self.canvas.delete(self.image1) # remove the previous image

        self.image1 = self.canvas.create_image((5,5), anchor='nw', image=self.render)
#--------------------------------write inpu file to jpg file and display------------------------------------
    def WriteImage(self):
        if self.Label is not None:
            self.Label.destroy()
            self.btn.destroy()
            self.varentry.destroy()
        if self.Label2 is not None:
            self.Label2.destroy()
            self.btn2.destroy()
            self.varentry2.destroy()
        if self.Label3 is not None:
            self.Label3.destroy()
            self.btn3.destroy()
            for i in range(9):
                self.maskentry[i].destroy()
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image
        
        self.newFileName = self.filename
        
        if imghdr.what(self.filename) == 'bmp':
            self.newFileName = self.filename[0:self.filename.find(".bmp")]+".jpg"
            self.origload.save(self.newFileName, quality=100)
            self.load2 = Image.open(self.newFileName)
        elif imghdr.what(self.filename) == 'ppm':
            self.newFileName = self.filename[0:self.filename.find(".ppm")]+".jpg"
            self.origload.save(self.newFileName, quality=100)
            self.load2 = Image.open(self.newFileName)
        else:
            self.load2 = self.load

        w, h = self.load2.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=300 or h >=300) and (h >= w)):
            self.load2 = self.load2.resize((int(300*ratio2), 300), Image.ANTIALIAS)
        elif ((w >=300 or h >=300) and (h < w)):
            self.load2 = self.load2.resize((300, int(300*ratio1)), Image.ANTIALIAS)
        self.render2 = ImageTk.PhotoImage(self.load2) #must keep a reference to this
        self.image2 = self.canvas.create_image((390,5), anchor='nw', image=self.render2)
#--------------------------------generate brighness Hstogram of the input image-----------------------------
    def Hstogram(self):
        if self.Label is not None:
            self.Label.destroy()
            self.btn.destroy()
            self.varentry.destroy()
        if self.Label2 is not None:
            self.Label2.destroy()
            self.btn2.destroy()
            self.varentry2.destroy()
        if self.Label3 is not None:
            self.Label3.destroy()
            self.btn3.destroy()
            for i in range(9):
                self.maskentry[i].destroy()
        if self.image4 is not None: # if an image was already loaded
            self.canvas.delete(self.image4) # remove the previous image
        if self.image3 is not None: # if an image was already loaded
            self.canvas.delete(self.image3) # remove the previous image
        self.brightness = [0] * 256
        load = Image.open(self.filename)
        load = load.convert("L")
        self.greyleveldata = list(load.getdata())
        for pixel in self.greyleveldata:
            self.brightness[pixel]+= 1

        mybar = plt.bar(range(256), self.brightness, align='edge', color='r')

        plt.xlabel('Intensity')
        plt.ylabel('Frequency')
        plt.title('Image Histogram')


        plt.savefig("histogram.png")
        plt.clf()
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image

        self.load2 = Image.open("histogram.png")
        w, h = self.load2.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=300 or h >=300) and (h >= w)):
            self.load2 = self.load2.resize((int(350*ratio2), 300), Image.ANTIALIAS)
        elif ((w >=300 or h >=300) and (h < w)):
            self.load2 = self.load2.resize((300, int(300*ratio1)), Image.ANTIALIAS)
        self.render2 = ImageTk.PhotoImage(self.load2) #must keep a reference to this
        self.image2 = self.canvas.create_image((390,15), anchor='nw', image=self.render2)
#--------------------------------generate zero mean Gaussian noises-----------------------------------------
    def inputvar(self):
        if self.Label is not None:
            self.Label.destroy()
            self.btn.destroy()
            self.varentry.destroy()
        if self.Label2 is not None:
            self.Label2.destroy()
            self.btn2.destroy()
            self.varentry2.destroy()
        if self.Label3 is not None:
            self.Label3.destroy()
            self.btn3.destroy()
            for i in range(9):
                self.maskentry[i].destroy()
        if self.image4 is not None: # if an image was already loaded
            self.canvas.delete(self.image4) # remove the previous image
        if self.image3 is not None: # if an image was already loaded
            self.canvas.delete(self.image3) # remove the previous image
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image
        self.Label = tk.Label(text='Var:')
        self.Label.place(x=310, y=150)
        var = tk.StringVar(value='0')
        self.varentry = tk.Entry(width=10, textvariable=var)
        self.varentry.place(x=310, y=170)
        self.btn = tk.Button(text="enter", command=self.zeromeanGaussiannoises)
        self.btn.place(x=310, y=190)
    def zeromeanGaussiannoises(self):
        if self.image1 is not None:
            load = Image.open(self.filename)
            load = load.convert("L")
            w, h = load.size#width, height
            ratio1 = h/w
            ratio2 = w/h
            if w%2 != 0:
                w = w - 1
                load = load.resize((w, h), Image.ANTIALIAS)

            greyleveldata = list(load.getdata())

            fdata = np.zeros((h, w), dtype=np.uint8)

            var = int(self.varentry.get())
            sigma = var**0.5#step1
            gnoise = []
            for x in range(h):
                for y in range(0,w-1,2):
                    r = random.random()
                    miu = random.random()#step2

                    z1 = sigma * math.cos(2*math.pi*miu)*math.sqrt(-2*math.log(r))
                    gnoise.append(z1)
                    z2 = sigma * math.sin(2*math.pi*miu)*math.sqrt(-2*math.log(r))#step3
                    gnoise.append(z2)

                    temp1 = greyleveldata[x*w+y] + z1
                    temp2 = greyleveldata[x*w+y+1] + z2#step4

                    if temp1 < 0:
                        greyleveldata[x*w+y] = 0
                    elif temp1 > 255:
                        greyleveldata[x*w+y] = 255
                    else:
                        greyleveldata[x*w+y] = temp1

                    if temp2 < 0:
                        greyleveldata[x*w+y+1] = 0
                    elif temp2 > 255:
                        greyleveldata[x*w+y+1] = 255
                    else:
                        greyleveldata[x*w+y+1] = temp2

            img = Image.new("L", (w,h))
            img.putdata(greyleveldata)
            
            w, h = img.size#width, height
            ratio1 = h/w
            ratio2 = w/h

            if self.image3 is not None: # if an image was already loaded
                self.canvas.delete(self.image3) # remove the previous image

            if ((w >=300 or h >=300) and (h >= w)):
                img = img.resize((int(300*ratio2), 300), Image.ANTIALIAS)
            elif ((w >=300 or h >=300) and (h < w)):
                img = img.resize((300, int(300*ratio1)), Image.ANTIALIAS)
            self.render3 = ImageTk.PhotoImage(img) #must keep a reference to this

            self.image3 = self.canvas.create_image((5,460), anchor='w', image=self.render3)

            a = np.array(gnoise)

            plt.hist(a, bins=100, density=True)
            plt.savefig("gnoise.png")
            plt.clf()
            self.load2 = Image.open("gnoise.png")
            w, h = self.load2.size
            ratio1 = h/w
            ratio2 = w/h
            if ((w >=300 or h >=300) and (h >= w)):
                self.load2 = self.load2.resize((int(300*ratio2), 300), Image.ANTIALIAS)
            elif ((w >=300 or h >=300) and (h < w)):
                self.load2 = self.load2.resize((300, int(300*ratio1)), Image.ANTIALIAS)
            self.render2 = ImageTk.PhotoImage(self.load2) #must keep a reference to this
            self.image2 = self.canvas.create_image((390,15), anchor='nw', image=self.render2)
#--------------------------------generate Discrete wavelet transform----------------------------------------
    def inputlayernum(self):
        if self.Label is not None:
            self.Label.destroy()
            self.btn.destroy()
            self.varentry.destroy()
        if self.Label3 is not None:
            self.Label3.destroy()
            self.btn3.destroy()
            for i in range(9):
                self.maskentry[i].destroy()
        w, h = self.origload.size
        if self.image4 is not None: # if an image was already loaded
            self.canvas.delete(self.image4) # remove the previous image
        if self.image3 is not None: # if an image was already loaded
            self.canvas.delete(self.image3) # remove the previous image
        if self.image2 is not None: # if an image was already loaded
            self.canvas.delete(self.image2) # remove the previous image
        self.Label2 = tk.Label(text='Layers:')
        self.Label2.place(x=310, y=150)
        var = tk.StringVar(value='1')
        self.varentry2 = tk.Entry(width=10, textvariable=var)
        self.varentry2.place(x=310, y=170)
        self.btn2 = tk.Button(text="enter", command=self.Haarwavelet)
        self.btn2.place(x=310, y=190)
    def Haarwavelet(self):
        self.Label2.destroy()
        self.btn2.destroy()
        if self.image1 is not None:
            load = Image.open(self.filename)
            m, n = load.size
            load = load.convert("L")

            level = int(self.varentry2.get())
            self.varentry2.destroy()
            plt.figure('Haarwavelet')
            if level == 1:
                if m % 2 != 0 or n % 2 != 0:
                    load = load.resize((m - m%2, n - n%2), Image.ANTIALIAS)

                coeffs = pywt.wavedec2(load, 'haar', level=level)
                cA, (cH, cV, cD) = coeffs
                AH = np.concatenate([cA, cH], axis=1)
                VD = np.concatenate([cV, cD], axis=1)
                img = np.concatenate([AH, VD], axis=0)
            elif level == 2:
                if m % 4 != 0 or n % 4 != 0:
                    load = load.resize((m - m%4, n - n%4), Image.ANTIALIAS)


                coeffs = pywt.wavedec2(load, 'haar', level=level)
                cA2, (cH2, cV2, cD2), (cH1, cV1, cD1) = coeffs

                AH2 = np.concatenate([cA2, cH2+510], axis=1)
                VD2 = np.concatenate([cV2+510, cD2+510], axis=1)
                cA1 = np.concatenate([AH2, VD2], axis=0)


                AH = np.concatenate([cA1, (cH1+255)*2], axis=1)
                VD = np.concatenate([(cV1+255)*2, (cD1+255)*2], axis=1)
                img = np.concatenate([AH, VD], axis=0)

            plt.imshow(img,'gray', interpolation='nearest')
            plt.axis('off')
            plt.savefig("Haarwavelet.png", bbox_inches='tight',pad_inches = 0)
            plt.clf()

            if self.image2 is not None: # if an image was already loaded
                self.canvas.delete(self.image2) # remove the previous image

            self.load2 = Image.open("Haarwavelet.png")
            w, h = self.load2.size
            ratio1 = h/w
            ratio2 = w/h
            if ((w >=350 or h >=350) and (h >= w)):
                self.load2 = self.load2.resize((int(350*ratio2), 350), Image.ANTIALIAS)
            elif ((w >=350 or h >=350) and (h < w)):
                self.load2 = self.load2.resize((350, int(350*ratio1)), Image.ANTIALIAS)
            self.render2 = ImageTk.PhotoImage(self.load2) #must keep a reference to this
            self.image2 = self.canvas.create_image((390,5), anchor='nw', image=self.render2)
#--------------------------------generate brighness Hstogram and histogram equalization---------------------
    def histogramequalization(self):
        if self.image1 is not None:
            #clear unnecessary items on the canvas
            if self.Label is not None:
                self.Label.destroy()
                self.btn.destroy()
                self.varentry.destroy()
            if self.Label2 is not None:
                self.Label2.destroy()
                self.btn2.destroy()
                self.varentry2.destroy()
            if self.image4 is not None:
                self.canvas.delete(self.image4)
            if self.image3 is not None:
                self.canvas.delete(self.image3)
            if self.image2 is not None:
                self.canvas.delete(self.image2)
            #step1
            self.Hstogram()
            #step2
            gmin = 0
            for index in self.brightness:
                if index>0:
                    break
                gmin += 1
            #step3
            Hc = [0] * 256
            Hc[0] = self.brightness[0]
            for g in range(1, 255):
                Hc[g] = Hc[g-1]+self.brightness[g]
            Hmin = Hc[gmin]
            #step4
            T = [0] * 256
            MN = len(self.greyleveldata)
            for g in range(256):
                T[g] = round(((Hc[g]-Hmin)/(MN-Hmin))*(255))
            #step5
            for i in range(MN):
                self.greyleveldata[i] = T[self.greyleveldata[i]]

            w, h = self.origload.size

            array = np.array(self.greyleveldata).reshape(h, w)
            new_image = Image.fromarray(array)

            self.load3 = new_image
            w, h = self.load3.size
            ratio1 = h/w
            ratio2 = w/h
            if ((w >=300 or h >=300) and (h >= w)):
                self.load3 = self.load3.resize((int(300*ratio2), 300), Image.ANTIALIAS)
            elif ((w >=300 or h >=300) and (h < w)):
                self.load3 = self.load3.resize((300, int(300*ratio1)), Image.ANTIALIAS)
            self.render3 = ImageTk.PhotoImage(self.load3) #must keep a reference to this
            self.image3 = self.canvas.create_image((5,460), anchor='w', image=self.render3)

            #plot Hstogram
            ebrightness = [0] * 256
            for pixel in self.greyleveldata:
                ebrightness[pixel]+= 1

            mybar = plt.bar(range(256), ebrightness, align='edge', color='r')

            plt.xlabel('Intensity')
            plt.ylabel('Frequency')
            plt.title('Histogram equalization')

            plt.savefig("histogramequalization.png")
            plt.clf()
            if self.image4 is not None: # if an image was already loaded
                self.canvas.delete(self.image4) # remove the previous image

            self.load4 = Image.open("histogramequalization.png")
            w, h = self.load4.size
            ratio1 = h/w
            ratio2 = w/h
            if ((w >=300 or h >=300) and (h >= w)):
                self.load4 = self.load4.resize((int(350*ratio2), 300), Image.ANTIALIAS)
            elif ((w >=300 or h >=300) and (h < w)):
                self.load4 = self.load4.resize((300, int(300*ratio1)), Image.ANTIALIAS)
            self.render4 = ImageTk.PhotoImage(self.load4) #must keep a reference to this
            self.image4 = self.canvas.create_image((395,460), anchor='w', image=self.render4)
#--------------------------------Image smoothing and edge detection-----------------------------------------
    def maskinput(self):
        if self.image1 is not None:
            if self.Label is not None:
                self.Label.destroy()
                self.btn.destroy()
                self.varentry.destroy()
            if self.Label2 is not None:
                self.Label2.destroy()
                self.btn2.destroy()
                self.varentry2.destroy()
            if self.image4 is not None: # if an image was already loaded
                self.canvas.delete(self.image4) # remove the previous image
            if self.image3 is not None: # if an image was already loaded
                self.canvas.delete(self.image3) # remove the previous image
            if self.image2 is not None: # if an image was already loaded
                self.canvas.delete(self.image2) # remove the previous image
            self.Label3 = tk.Label(text='Mask:')
            self.Label3.place(x=390, y=50)
            var = [None] * 9
            for i in range(9):
                var[i] = tk.StringVar(value = 0)
            for i in range(3):
                for j in range(3):
                    self.maskentry[i*3+j] = tk.Entry(width=3, textvariable=var[i*3 + j])
                    self.maskentry[i*3+j].place(x=390+j*50, y=70+i*30)
            self.btn3 = tk.Button(text="enter", command=self.convolution)
            self.btn3.place(x=390, y=160)
    def convolution(self):
        load = Image.open(self.filename)
        load = load.convert("L")
        w, h = load.size#width, height
        mask = np.zeros((3, 3))
        for i in range(3):
                for j in range(3):
                    mask[i][j] = float(self.maskentry[8-(i*3+j)].get())
        output = np.zeros((h, w))
        image_padded = np.zeros((h + 2, w + 2))
        image_padded[1:-1, 1:-1] = load
        for y in range(h):
            for x in range(w):
                output[y,x]=(mask*image_padded[y:y+3,x:x+3]).sum()
                if output[y,x]<0:
                    output[y,x] = 0
                elif output[y,x] > 255:
                    output[y,x] = 255
                else:
                    output[y,x] = int(output[y,x])
        new_image = Image.fromarray(output)
        self.load3 = new_image
        w, h = self.load3.size
        ratio1 = h/w
        ratio2 = w/h
        if ((w >=300 or h >=300) and (h >= w)):
            self.load3 = self.load3.resize((int(300*ratio2), 300), Image.ANTIALIAS)
        elif ((w >=300 or h >=300) and (h < w)):
            self.load3 = self.load3.resize((300, int(300*ratio1)), Image.ANTIALIAS)
        self.render3 = ImageTk.PhotoImage(self.load3) #must keep a reference to this
        self.image3 = self.canvas.create_image((5,460), anchor='w', image=self.render3)



root = tk.Tk()
root.geometry("%dx%d" % (695, 615))
root.title("AIP")
app = Window(root)
app.pack(fill=tk.BOTH, expand=1)
root.mainloop()
