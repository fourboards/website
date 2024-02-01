import io
import os
from pathlib import Path
import pandas as pd
import requests
from bs4 import BeautifulSoup
from PIL import Image
from selenium import webdriver
import validators

def get_content_from_url(url):
   driver = webdriver.Chrome()  # Add "executable_path=" if the driver is in a custom directory.
   driver.get(url)
   driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
   page_content = driver.page_source
   driver.quit()  # You don't need the browser instance for further steps.
   return page_content


def parse_image_urls(content):
   soup = BeautifulSoup(content, features="html.parser")
   images = soup.findAll('img')
   results = []
   for image in images:
      for attr in ['src', 'data-image']:
         try:
            source = image.attrs[attr]
            if validators.url(source):
               print(f"Valid URL: {source}")
               results.append(source)
               break
         except:
            pass

   return results



def save_urls_to_csv(image_urls):
   df = pd.DataFrame({"links": image_urls})
   df.to_csv("links.csv", index=False, encoding="utf-8")


def get_and_save_image_to_file(image_url, output_dir):
   response = requests.get(image_url, headers={"User-agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/113.0.0.0 Safari/537.36"})
   image_content = response.content
   image_file = io.BytesIO(image_content)
   image = Image.open(image_file).convert("RGB")
   file_name = image_url.rsplit('/', 1)[-1]
   if file_name.find('?') > 0:
      format = file_name.rsplit('?', 1)[-1]
      file_name = file_name.rsplit('?', 1)[0]
      name = file_name.rsplit('.', 1)[0]
      extension = file_name.rsplit('.', 1)[-1]
      file_name = name + "_" + format + "." + extension

   print(file_name)
   file_path = output_dir / file_name
   image.save(file_path)

def download_images(url: str, output_dir: Path):
   content = get_content_from_url(url)

   image_urls = parse_image_urls(content=content)
   save_urls_to_csv(image_urls)

   for image_url in image_urls:
       get_and_save_image_to_file(
           image_url, output_dir=output_dir,
       )

pages = [
"https://fourboards.co.uk/home",
"https://fourboards.co.uk/cycle-race-timing-system",
"https://fourboards.co.uk/jamiroquai-control-board",
"https://fourboards.co.uk/touchpad-support",
"https://fourboards.co.uk/touchpad",
"https://fourboards.co.uk/touchpad-pro",
"https://fourboards.co.uk/scalextric-start-gate",
"https://fourboards.co.uk/nixie-clock",
"https://fourboards.co.uk/xor-ruler",
"https://fourboards.co.uk/led-card",
"https://fourboards.co.uk/tvm802-openpnp-upgrade",
"https://fourboards.co.uk/rubix-cube-solving-robot",
"https://fourboards.co.uk/atmel-ice-breakout",
"https://fourboards.co.uk/customisable-led-panel",
"https://fourboards.co.uk/led-guitar",
"https://fourboards.co.uk/cnc-upgrade",
"https://fourboards.co.uk/rgb-candles",
"https://fourboards.co.uk/bascetta-star-light",
"https://fourboards.co.uk/sr-2016",
"https://fourboards.co.uk/z-probe-board",
"https://fourboards.co.uk/led-discs",
"https://fourboards.co.uk/edit-toronto",
"https://fourboards.co.uk/qr-code-clock",
"https://fourboards.co.uk/swim-ring",
"https://fourboards.co.uk/diy-jbc",
"https://fourboards.co.uk/deborah-milner-led-dress",
"https://fourboards.co.uk/8x8x8-rgb-led-cube",
"https://fourboards.co.uk/morilondon-candles",
"https://fourboards.co.uk/xor-promotional-dice",
"https://fourboards.co.uk/overlay-library",
"https://fourboards.co.uk/touchpad-production-equipment",
"https://fourboards.co.uk/wireless-dmx",
"https://fourboards.co.uk/cycle-trainer",
"https://fourboards.co.uk/procharge",
"https://fourboards.co.uk/procharge-support",
"https://fourboards.co.uk/dragon-eyes",
"https://fourboards.co.uk/rgb-led-cube",
"https://fourboards.co.uk/bike-speakers",
]

if __name__ == "__main__":  # Only executes if imported as a main file.
   for page in pages:
      output_dir = Path("C:/Users/10sta/Desktop/Website_files/" + page.rsplit('/', 1)[-1])
      os.mkdir(output_dir)
      download_images(url=page, output_dir=output_dir)
