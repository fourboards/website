import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse


def get_all_pages(domain, start_page):
   # Set up a list to store the discovered pages
   all_pages = [start_page]

   # Set up a set to store visited pages to avoid duplicates and infinite loops
   visited_pages = set([start_page])

   # Continue crawling as long as there are pages to visit
   while all_pages:
      current_page = all_pages.pop(0)  # Get the first page from the list

      try:
         # Send a GET request to the current page
         response = requests.get(current_page)

         # Check if the request was successful (status code 200)
         if response.status_code == 200:
            # Parse the HTML content of the page
            soup = BeautifulSoup(response.text, 'html.parser')

            # Find all links on the page
            links = soup.find_all('a', href=True)

            # Extract and normalize URLs
            for link in links:
               href = link.get('href')
               full_url = urljoin(current_page, href)
               parsed_url = urlparse(full_url)

               # Check if the link is within the specified domain and not already visited
               if parsed_url.netloc == domain and full_url not in visited_pages:
                  all_pages.append(full_url)  # Add the new page to the list
                  visited_pages.add(full_url)  # Mark the page as visited

      except Exception as e:
         print(f"Error accessing {current_page}: {e}")

   return visited_pages

def get_pages(domain: str, start_url: str):
   result = get_all_pages(domain, start_url)

   # Print the list of discovered pages
   print("Discovered Pages:")
   for page in result:
      print(page)


if __name__ == "__main__":  # Only executes if imported as a main file.
   get_pages(domain="fourboards.co.uk", start_url="https://fourboards.co.uk")