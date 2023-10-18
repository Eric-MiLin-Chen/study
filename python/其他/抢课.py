from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.chrome.options import Options
from time import sleep

account = input('请输入学号：')
password = input('请输入密码：')
classes = []

while True:
    tmp = input('请输入（课程号 教师号）与回车，以0作为输入完毕：').split()
    if tmp == ['0']:
        break
    else:
        classes.append(tmp)

chrome_options = Options()
# chrome_options.add_argument('--headless')
chrome_options.add_argument('--incognito')
chrome_options.add_experimental_option(
    "excludeSwitches", ['enable-automation', 'enable-logging'])
driver = webdriver.Chrome(options=chrome_options)
sleep(0.5)
driver.get('http://xk.autoisp.shu.edu.cn/')
sleep(0.5)
input("请输入回车以开始选课...")
for i in classes:
    driver.find_element(By.XPATH, '//*[@id = "username"]').send_keys(account)
    driver.find_element(By.XPATH, '//*[@id = "password"]').send_keys(password)
    driver.find_element(By.ID, 'submit-button').click()
    sleep(0.2)
    driver.find_element(By.XPATH, '//*[@name = "rowterm"]').click()
    sleep(0.2)
    driver.find_element(By.XPATH, '//button[@type = "submit"]').click()
    sleep(0.2)
    driver.find_element(
        By.XPATH, '//*[@id = "CourseSelectionStudentFuzzyQuery"]').click()
    # driver.find_element(
    #     By.XPATH, '//*[@id = "StudentQueryQueryCourse"]').click()
    sleep(0.2)
    driver.find_element(By.XPATH, '//*[@name = "CID"]').send_keys(i[0])
    driver.find_element(By.XPATH, '//*[@name = "TeachNo"]').send_keys(i[1])
    sleep(0.2)
    driver.find_element(By.XPATH, '//button[@id="QueryAction"]').click()
    sleep(0.2)
    driver.find_element(By.XPATH, '//*[@name = "checkclass"]').click()
    sleep(0.2)
    driver.find_element(
        By.XPATH, '//button[@id = "CourseCheckAction"]').click()
    driver.find_element(By.XPATH, '//span[text() = "关闭"]').click()
input()

driver.quit()
