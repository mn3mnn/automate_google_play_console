import os
import sys
import time
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.action_chains import ActionChains


###########################################################################################
# URL = 'https://play.google.com/console/u/0/developers/8337348834814397257/'

URL = ""
CURR_SCRIPT_PATH = os.path.dirname(sys.executable)
PATH_TO_DRIVER = CURR_SCRIPT_PATH + '\\Program files\\geckodriver.exe'
PATH_TO_FF = None
PATH_TO_FF_PROFILE = None
###########################################################################################
CSV_FILE_PATH = CURR_SCRIPT_PATH + '\\Game data\\CSV\\'
APP_ICON_PATH = CURR_SCRIPT_PATH + '\\Game data\\App icon\\'
FEATURE_GRAPHIC_PATH = CURR_SCRIPT_PATH + '\\Game data\\Feature graphic\\'
SCREENSHOTS_PATH = CURR_SCRIPT_PATH + '\\Game data\\Screenshots\\'
RELEASE_PATH = CURR_SCRIPT_PATH + '\\Game data\\Release\\'
###########################################################################################

# for debugging
# URL = ""
# # Join the current directory and the script name to get the full path
# CURR_SCRIPT_PATH = os.getcwd()
#
# PATH_TO_DRIVER = CURR_SCRIPT_PATH + '\\Program files\\geckodriver.exe'
# PATH_TO_FF = ""
# PATH_TO_FF_PROFILE = ""
# ###########################################################################################
# CSV_FILE_PATH = CURR_SCRIPT_PATH + '\\Game data\\CSV\\'
# APP_ICON_PATH = CURR_SCRIPT_PATH + '\\Game data\\App icon\\'
# FEATURE_GRAPHIC_PATH = CURR_SCRIPT_PATH + '\\Game data\\Feature graphic\\'
# SCREENSHOTS_PATH = CURR_SCRIPT_PATH + '\\Game data\\Screenshots\\'
# RELEASE_PATH = CURR_SCRIPT_PATH + '\\Game data\\Release\\'

# ###########################################################################################

# create debugging file
DEBUG_FILE = open(CURR_SCRIPT_PATH + '\\Program files\\debug.txt', 'w')

# try to read ff path from txt file in the same directory
try:
    # READ FF EXE PATH
    file = open(CURR_SCRIPT_PATH + '\\ffPath.txt', 'r')
    PATH_TO_FF = file.readline().strip()
    PATH_TO_FF.strip('\n')
    # READ FF PROFILE PATH
    PATH_TO_FF_PROFILE = file.readline().strip()
    PATH_TO_FF_PROFILE.strip('\n')
    file.close()


except Exception as e:
    DEBUG_FILE.write('error reading firefox path' + '\n========================================================\n')
    DEBUG_FILE.write(str(e) + '\n========================================================\n')
    DEBUG_FILE.flush()
    sys.exit(1)

# try to read file names from the Game data directory
try:
    csv_file_dir = CSV_FILE_PATH + os.listdir(CSV_FILE_PATH)[0]
    app_icon_dir = APP_ICON_PATH + os.listdir(APP_ICON_PATH)[0]
    feature_graphic_dir = FEATURE_GRAPHIC_PATH + os.listdir(FEATURE_GRAPHIC_PATH)[0]
    screenshots = [(SCREENSHOTS_PATH + name) for name in os.listdir(SCREENSHOTS_PATH)]
    release_dir = RELEASE_PATH + os.listdir(RELEASE_PATH)[0]

except Exception as e:
    DEBUG_FILE.write('error in Game data files' + '\n========================================================\n')
    DEBUG_FILE.write(str(e) + '\n========================================================\n')
    DEBUG_FILE.flush()


# global variables
driver = None
# data from the GUI APP to be filled in the form
INPUT_DATA = []
# id for the created app
APP_ID = ""

###########################################################################################


# read data from data file
def get_data_file():
    global INPUT_DATA, CURR_SCRIPT_PATH, DEBUG_FILE
    try:
        with open(CURR_SCRIPT_PATH + '\\Program files\\inputData.txt', 'r', encoding="utf-8") as f:
            INPUT_DATA = f.read().splitlines()
            f.close()
        return True
    except Exception as e:
        DEBUG_FILE.write("error reading input data" + '\n========================================================\n')
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        return False


# open ff and connect to the driver
def open_browser_and_driver():
    global driver, PATH_TO_FF, CURR_SCRIPT_PATH, PATH_TO_DRIVER, DEBUG_FILE
    try:
        profile = webdriver.FirefoxProfile(PATH_TO_FF_PROFILE)
        # Pass the Firefox profile to the Firefox driver
        driver = webdriver.Firefox(firefox_profile=profile,
                                    executable_path=PATH_TO_DRIVER,
                                    firefox_binary=PATH_TO_FF)
        driver.maximize_window()

    except Exception as e:
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        DEBUG_FILE.write("error opening driver or firefox" + '\n========================================================\n')
        return False

    return True


# open google console and wait for user to login if needed
def open_google_console():
    global driver, URL, DEBUG_FILE
    try:
        # open google console
        driver.get(URL)
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(EC.url_matches(URL))
        return True

    except Exception as e:
        # if user didn't sign in or network error
        DEBUG_FILE.write(
            "user didn't sign in or network error" + '\n========================================================\n')
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        return False


# fill the earliest form and initialize APP_ID variable
def fill_main_form():
    global driver, INPUT_DATA, APP_ID, URL, DEBUG_FILE
    try:
        action = ActionChains(driver)
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(EC.element_to_be_clickable(
            (By.XPATH, '//material-input[@debug-id=\'app-name-input\']//input[@type=\'text\']')))
        # fill app name
        driver.find_element(By.XPATH,
                            '//material-input[@debug-id=\'app-name-input\']//input[@type=\'text\']') \
            .send_keys(INPUT_DATA[0])
        # select language
        try:
            # if the language is not english choose it, otherwise continue (en by default)
            if INPUT_DATA[1].find("English") == -1:

                action.move_to_element(driver.find_element(By.XPATH, '//div[@aria-label=\'Choose default language\']'))
                action.click().perform()
                time.sleep(0.5)
                # action.scroll_to_element(driver.find_element(By.XPATH, f'//span[contains(text(),\'{INPUT_DATA[1]}\')]'))
                # action.perform()
                # time.sleep(0.5)

                driver.execute_script('arguments[0].scrollIntoView(true);', driver.find_element(By.XPATH, f'//span[contains(text(),\'{INPUT_DATA[1]}\')]'))
                action.move_to_element(driver.find_element(By.XPATH, f'//span[contains(text(),\'{INPUT_DATA[1]}\')]'))
                action.perform()
                action.click().perform()

        except Exception as e:
            DEBUG_FILE.write(
                "error selecting language " + '\n========================================================\n')
            driver.find_element(By.XPATH, '//div[contains(text(),\'App name\')]').click()

        # select 'Game', 'Free'
        action.move_to_element(
            driver.find_element(By.XPATH, '//material-radio[@debug-id=\'game-radio\']//input[@role=\'radio\']'))
        action.double_click().perform()
        action.move_to_element(
            driver.find_element(By.XPATH, '//material-radio[@debug-id=\'free-radio\']//input[@role=\'radio\']'))
        action.click().perform()
        # wait until message box is shown
        WebDriverWait(driver, 5).until(
            EC.presence_of_element_located((By.XPATH, '//console-message[@debug-id=\'free-app-message\']')))

        # check boxes
        # scroll down to footer
        # action.scroll_to_element(driver.find_element(By.XPATH, '//div[@debug-id=\'chrome-footer-container\']//div'))
        # action.perform()
        driver.execute_script('arguments[0].scrollIntoView(true);',
                              driver.find_element(By.XPATH, '//div[@debug-id=\'chrome-footer-container\']//div'))

        action.move_to_element(driver.find_element(By.XPATH,
                                                   '//material-checkbox[@debug-id=\'guidelines-checkbox\']//input['
                                                   '@role=\'checkbox\']'))
        action.click().perform()
        time.sleep(0.3)
        action.move_to_element(driver.find_element(By.XPATH,
                                                   '//material-checkbox[@debug-id=\'export-laws-checkbox\']//input['
                                                   '@role=\'checkbox\']'))
        action.click().perform()
        time.sleep(0.3)

        # click 'Create app'
        driver.find_element(By.XPATH, '//div[contains(text(),\'Create app\')]').click()
        # wait for dashboard page to be loaded
        WebDriverWait(driver, 120).until(EC.visibility_of_element_located((By.XPATH, '//body[1]/div[1]/root['
                                                                                    '1]/console-chrome[1]/div[1]/div['
                                                                                    '1]/div[1]/div[1]/div['
                                                                                    '1]/page-router-outlet['
                                                                                    '1]/page-wrapper[1]/div['
                                                                                    '1]/app-dashboard-page['
                                                                                    '1]/console-page-header[1]/div['
                                                                                    '1]/div[1]/div[1]/console-header['
                                                                                    '1]/div[1]/div[1]/div[1]/div['
                                                                                    '1]/div[1]/div[1]/simple-html['
                                                                                    '1]/span[1]')))
        APP_ID = driver.current_url[len(URL): len(URL) + 24]
        return True
    except Exception as e:
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        return False


# fill app content section
def fill_app_content_section():
    global driver, INPUT_DATA, APP_ID, URL, DEBUG_FILE
    action = ActionChains(driver)

    # fill privacy policy
    try:
        # get privacy policy page
        driver.get(URL + APP_ID + 'app-content/privacy-policy')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//input[@aria-label=\'Privacy policy URL\']')))
        # fill privacy policy
        driver.find_element(By.XPATH, '//input[@aria-label=\'Privacy policy URL\']').send_keys(INPUT_DATA[2])
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        # wait for message box with msg 'your changes have been saved' to be shown
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH,
                                              '//*[@id="main-content"]/div/div['
                                              '1]/page-router-outlet/page-wrapper/div/app-content-privacy-policy-page'
                                              '/div/form-bottom-bar/bottom-bar-base/div/div/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling privacy policy" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # ads page
    try:
        # get ads page
        driver.get(URL + APP_ID + 'app-content/ads-declaration')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-ads'
                                                        '-declaration-page/div/console-block-1-column['
                                                        '2]/div/div/console-form/console-form-row/div/div[2]/div['
                                                        '1]/material-radio-group/material-radio[1]/div[1]')))
        # check Yes
        driver.find_element(By.XPATH, '//material-radio[1]//div[1]//input[1]').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        # wait for message box with msg 'your changes have been saved' to be shown
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-ads'
                                                        '-declaration-page/div/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'), 'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling ads page" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # App access page
    try:
        # get app access page
        driver.get(URL + APP_ID + 'app-content/testing-credentials')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-testing'
                                                        '-credentials-page/console-block-1-column/div/div/console'
                                                        '-form/console-form-expandable-section['
                                                        '1]/div/div/material-radio/div[1]/div[1]')))
        # click on first radio button
        driver.find_element(By.XPATH, '//console-form-expandable-section['
                                      '@debug-id=\'login-not-required-expandable-section\']//div//div'
                                      '//material-radio[@aria-checked=\'false\']//div//input['
                                      '@role=\'radio\']').click()
        # click save
        driver.find_element(By.XPATH, '//*[@id="main-content"]/div/div['
                                      '1]/page-router-outlet/page-wrapper/div/app-content-testing-credentials-page'
                                      '/form-bottom-bar/bottom-bar-base/div/div/div/div['
                                      '2]/console-button-set/div/button[1]').click()
        # wait for message box with msg 'your changes have been saved' to be shown
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-testing'
                                                        '-credentials-page/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'), 'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling app access" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # content rating page
    try:
        # get content rating questionnaire page
        driver.get(URL + APP_ID + 'app-content/content-rating-overview')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//div[contains(text(),\'Start questionnaire\')]')))
        # click start
        driver.find_element(By.XPATH, '//div[contains(text(),\'Start questionnaire\')]').click()
        WebDriverWait(driver, 60).until(
            EC.visibility_of_element_located((By.XPATH, '//input[@type=\'email\']')))
        # input email
        driver.find_element(By.XPATH, '//input[@type=\'email\']').send_keys(INPUT_DATA[3])
        # click game
        driver.find_element(By.XPATH, '//body//div//div[@aria-label=\'Category\']//div//div//div[1]//material-radio['
                                      '1]//div[1]//input[1]').click()
        # click next
        driver.find_element(By.XPATH, '//div[contains(text(),\'Next\')]').click()

        # wait for first question to be loaded
        WebDriverWait(driver, 60).until(
            EC.visibility_of_element_located(
                (By.XPATH, '//span[normalize-space()=\'Violence, Blood, or Gory Images\']')))
        time.sleep(1)
        # click no for all questions
        c = 0
        for i in range(1, 15):
            driver.find_elements(By.XPATH, f'//input[@role=\'radio\']')[i + c].click()
            driver.find_elements(By.XPATH, f'//input[@role=\'radio\']')[i + c].location_once_scrolled_into_view
            # action.scroll_by_amount(0, 100).perform()
            c += 1
            time.sleep(0.7)

        # click save
        try:
            driver.find_element(By.XPATH, '//div[contains(text(),\'Save\')]').click()
            # wait for message box with msg 'your changes have been saved' to be shown
            WebDriverWait(driver, 60).until(
                EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                            '1]/page-router-outlet/page-wrapper/div/app-content-rating'
                                                            '-iarc-questionnaire-page/console-form/fill-questionnaire'
                                                            '-flow/form-bottom-bar/bottom-bar-base/div/div/div/div['
                                                            '1]/span'), 'Your changes have been saved'))
        except Exception as e:
            # click the vertical dots if save button is not visible
            driver.find_element(By.XPATH, '//i[normalize-space()=\'more_vert\']').click()
            time.sleep(3)
            # click save
            driver.find_element(By.XPATH, '//material-select-item[@aria-label=\'Save\']//span//span[1]').click()
            # wait for message box with msg 'your changes have been saved' to be shown
            WebDriverWait(driver, 60).until(
                EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                            '1]/page-router-outlet/page-wrapper/div/app-content-rating'
                                                            '-iarc-questionnaire-page/console-form/fill-questionnaire'
                                                            '-flow/form-bottom-bar/bottom-bar-base/div/div/div/div['
                                                            '1]/span'), 'Your changes have been saved'))
        time.sleep(1)
        # click next
        WebDriverWait(driver, 60).until(
            EC.element_to_be_clickable((By.XPATH, '//div[contains(text(),\'Next\')]')))
        driver.find_element(By.XPATH, '//div[contains(text(),\'Next\')]').click()

        # wait for submit btn to be loaded
        WebDriverWait(driver, 60).until(
            EC.visibility_of_element_located((By.XPATH, '//div[normalize-space()=\'Submit\']')))
        # click submit
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Submit\']').click()
        try:
            WebDriverWait(driver, 60).until(
                EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                            '1]/page-router-outlet/page-wrapper/div/app-content-rating'
                                                            '-overview-page/div/questionnaire-overview/console-section['
                                                            '1]/div/div/questionnaire-overview-table/labelled-field['
                                                            '1]/div/div[2]/div[1]/status-text/span[2]/simple-html/span'),
                                                 'Completed'))
        except:
            pass
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling content ratings" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # target audience page
    try:
        # get target audience page
        driver.get(URL + APP_ID + 'app-content/target-audience-content')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//span[contains(text(),\'Target age\')]')))
        # select ages
        # scroll to element
        driver.find_elements(By.XPATH, '//input[@role=\'checkbox\']')[3].location_once_scrolled_into_view
        for i in range(3, 6):
            driver.find_elements(By.XPATH, '//input[@role=\'checkbox\']')[i].click()
        # click next
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Next\']').click()
        time.sleep(1)
        # select yes
        driver.find_element(By.XPATH, '//material-radio[1]//div[1]//input[1]').click()
        # click next
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Next\']').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-target'
                                                        '-audience-content-page/form-bottom-bar/bottom-bar-base/div'
                                                        '/div/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling target audience" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # news app page
    try:
        # get page
        driver.get(URL + APP_ID + 'app-content/news-declaration')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//span[normalize-space()=\'News apps\']')))
        # select No
        driver.find_element(By.XPATH,
                            '//material-radio[@debug-id=\'app-type-radio-not-news\']//input[@role=\'radio\']').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-news'
                                                        '-declaration-page/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling news app" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # COVID19 page
    try:
        # get page
        driver.get(URL + APP_ID + 'app-content/regulated-health-apps')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//span[normalize-space()=\'COVID-19 contact tracing and '
                                                        'status apps\']')))
        # select last option
        driver.find_element(By.XPATH, '//material-checkbox[@debug-id=\'none\']//input[@role=\'checkbox\']').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-regulated'
                                                        '-health-apps-page/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write("error while filling covid19" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # data safety page
    try:
        # get page
        driver.get(URL + APP_ID + 'app-content/data-privacy-security')
        # try to wait for page to be loaded if a pop-up appears refresh page
        try:
            # wait for page to be loaded
            WebDriverWait(driver, 120).until(
                EC.element_to_be_clickable((By.XPATH, '//span[normalize-space()=\'Data safety\']')))
        except Exception as e:
            driver.get(URL + APP_ID + 'app-content/data-privacy-security')
            # wait for page to be loaded
            WebDriverWait(driver, 120).until(
                EC.element_to_be_clickable((By.XPATH, '//span[normalize-space()=\'Data safety\']')))
        # click import from csv
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Import from CSV\']').click()
        time.sleep(1)
        # upload file
        driver.find_element(By.XPATH, '//input[@type=\'file\']').send_keys(csv_file_dir)
        # wait for the uploading
        WebDriverWait(driver, 300).until(
            EC.visibility_of_element_located((By.XPATH, '//div[contains(text(),\'CSV file successfully uploaded\')]')))
        # click import
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Import\']').click()
        # wait for the pop-up
        WebDriverWait(driver, 60).until(
            EC.visibility_of_element_located((By.XPATH, '//div[contains(text(),\'Answers already entered into the '
                                                        'questionnaire wil\')]')))
        # click import on the pop-up
        driver.find_element(By.XPATH, '//*[@id="default-acx-overlay-container"]/div['
                                      '4]/material-dialog/focus-trap/div['
                                      '2]/div/footer/div/div/console-button-set/div/button[2]').click()
        for i in range(0, 3):
            # click next 3 times
            driver.find_element(By.XPATH, '//div[contains(text(),\'Next\')]').click()
            time.sleep(0.5)
        # click submit
        driver.find_element(By.XPATH, '//div[contains(text(),\'Submit\')]').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-play'
                                                        '-safety-labels-page/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'),
                                             'Your changes have been saved'))

    except Exception as e:
        DEBUG_FILE.write(
            "error while filling data safety" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # ADs id page
    try:
        # get page
        driver.get(URL + APP_ID + 'app-content/ad-id-declaration')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//span[normalize-space()=\'Advertising ID\']')))
        # scroll
        driver.find_element(By.XPATH, '//span[normalize-space()=\'Declaration\']').location_once_scrolled_into_view
        # select No
        driver.find_element(By.XPATH, '//material-radio[@debug-id=\'no-radio\']//input[@role=\'radio\']').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content-ad-id'
                                                        '-declaration-page/form-bottom-bar/bottom-bar-base/div/div'
                                                        '/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write("error while filling AD id" + '\n========================================================\n')
        return False

    # ================================================================================================================
    # government apps page
    try:
        # get page
        driver.get(URL + APP_ID + 'app-content/government-apps')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//span[normalize-space()=\'Government apps\']')))
        # select No
        driver.find_element(By.XPATH, '//material-radio[@debug-id=\'no-radio\']//input[@role=\'radio\']').click()
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/app-content'
                                                        '-government-apps-page/form-bottom-bar/bottom-bar-base/div'
                                                        '/div/div/div[1]/span'),
                                             'Your changes have been saved'))
    except Exception as e:
        DEBUG_FILE.write(
            "error while filling government app" + '\n========================================================\n')
        return False
    # ================================================================================================================

    return True


# fill app details and upload images
def fill_main_store_listing_section():
    try:
        # get page
        driver.get(URL + APP_ID + 'main-store-listing')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(
            EC.visibility_of_element_located((By.XPATH, '//simple-html//span[contains(text(),\'Main store listing\')]')))

        # scroll to app details
        driver.find_element(By.XPATH, '//span[normalize-space()=\'App details\']').location_once_scrolled_into_view
        # fill short description
        driver.find_element(By.XPATH, '//input[@aria-label=\'Short description of the app\']').click()
        driver.find_element(By.XPATH, '//input[@aria-label=\'Short description of the app\']').send_keys(INPUT_DATA[4])
        # fill full description
        for i in range(1, int(INPUT_DATA[5]) + 1):
            driver.find_element(By.XPATH, '//textarea[@aria-label=\'Full description of the app\']').send_keys(
                INPUT_DATA[5 + i] + '\n')

        # scroll to graphics
        driver.find_element(By.XPATH, '//span[normalize-space()=\'Graphics\']').location_once_scrolled_into_view
        # upload icon
        driver.find_element(By.XPATH, '//app-image-uploader[@debug-id=\'icon-uploader\']//input[@type=\'file\']')\
            .send_keys(app_icon_dir)
        # upload feature img
        driver.find_element(By.XPATH, '//app-image-uploader[@debug-id=\'feature-graphic-uploader\']//input['
                                      '@type=\'file\']').send_keys(feature_graphic_dir)
        try:
            # wait for icon
            WebDriverWait(driver, 300).until(
                EC.presence_of_element_located((By.XPATH, f'//img[@alt=\'{os.listdir(APP_ICON_PATH)[0]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading icon" + '\n========================================================\n')
        try:
            # wait for feature graphic
            WebDriverWait(driver, 300).until(
                EC.presence_of_element_located((By.XPATH, f'//img[@alt=\'{os.listdir(FEATURE_GRAPHIC_PATH)[0]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading feature graphic" + '\n========================================================\n')

        # scroll to screenshots
        driver.find_element(By.XPATH, '//span[normalize-space()=\'Phone\']').location_once_scrolled_into_view
        # get all screenshots as string
        all_screenshots = ""
        for screenshot in screenshots:
            all_screenshots += screenshot + '\n'
        all_screenshots = all_screenshots[:-1]
        # upload phone screenshots
        driver.find_element(By.XPATH, '//app-screenshots-uploader['
                                          '@debug-id=\'phone-screenshot-uploader\']//input['
                                          '@type=\'file\']').send_keys(all_screenshots)
        try:
            # wait for all phone screenshots
            for i in range(len(os.listdir(SCREENSHOTS_PATH))):
                WebDriverWait(driver, 300).until(
                    EC.presence_of_element_located((By.XPATH, f'//app-screenshots-uploader['
                                                              f'@debug-id=\'phone-screenshot-uploader\']//div//div'
                                                              f'//div//img[@alt=\''
                                                              f'{os.listdir(SCREENSHOTS_PATH)[i]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading phone screenshots" + '\n========================================================\n')

        # scroll to tablet
        driver.find_element(By.XPATH, '//span[normalize-space()=\'Tablet\']').location_once_scrolled_into_view
        # upload 7inch tablet screenshots
        driver.find_element(By.XPATH, '//app-screenshots-uploader[@debug-id=\'small-tablet-screenshot-uploader'
                                    '\']//input[@type=\'file\']').send_keys(all_screenshots)
        # upload 10inch tablet screenshots
        driver.find_element(By.XPATH, '//app-screenshots-uploader[@debug-id=\'regular-tablet-screenshot-uploader'
                                          '\']//input[@type=\'file\']').send_keys(all_screenshots)
        try:
            # wait for small tablet screenshots
            for i in range(len(os.listdir(SCREENSHOTS_PATH))):
                WebDriverWait(driver, 300).until(
                    EC.presence_of_element_located((By.XPATH, f'//app-screenshots-uploader[@debug-id=\'small-tablet-screenshot-uploader\']//div//div//div//img[@alt=\'{os.listdir(SCREENSHOTS_PATH)[i]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading tablet screenshots" + '\n========================================================\n')
        try:
            # wait for 10inch tablet screenshots
            for i in range(len(os.listdir(SCREENSHOTS_PATH))):
                WebDriverWait(driver, 300).until(
                    EC.presence_of_element_located((By.XPATH, f'//app-screenshots-uploader[@debug-id=\'regular-tablet-screenshot-uploader\']//div//div//div//img[@alt=\'{os.listdir(SCREENSHOTS_PATH)[i]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading tablet screenshots" + '\n========================================================\n')

        # scroll to chromebook
        driver.find_element(By.XPATH, '//span[normalize-space()=\'Chromebook\']').location_once_scrolled_into_view
        # upload chromebook screenshots
        driver.find_element(By.XPATH, '//app-screenshots-uploader[@debug-id=\'chromebook-screenshot-uploader'
                                        '\']//input[@type=\'file\']').send_keys(all_screenshots)
        try:
            # wait for all chromebook screenshots
            for i in range(len(os.listdir(SCREENSHOTS_PATH))):
                WebDriverWait(driver, 200).until(
                    EC.presence_of_element_located((By.XPATH, f'//app-screenshots-uploader['
                                                              f'@debug-id=\'chromebook-screenshot-uploader\']//div'
                                                              f'//div//div//img[@alt=\''
                                                              f'{os.listdir(SCREENSHOTS_PATH)[i]}\']')))
        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            DEBUG_FILE.write("error uploading chromebook screenshots" + '\n========================================================\n')

        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/main-store-listing'
                                                        '-page/form-bottom-bar/bottom-bar-base/div/div/div/div['
                                                        '1]/span'),
                                             'Your changes have been saved'))

    except Exception as e:
        DEBUG_FILE.write(
            "error while filling main store listing section" + '\n========================================================\n')
        return False

    return True


def fill_store_settings_section():
    try:
        action = ActionChains(driver)
        driver.get(URL + APP_ID + 'store-settings')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(EC.presence_of_element_located(
            (By.XPATH, '//simple-html//span[contains(text(),\'App category\')]')))
        # select category
        try:

            action.move_to_element(driver.find_element(By.XPATH, '//span[contains(text(),\'Select a category\')]'))
            action.click().perform()
            time.sleep(0.5)
            # action.scroll_to_element(driver.find_element(By.XPATH, f'//span[normalize-space()=\'{INPUT_DATA[-5]}\']'))
            # action.perform()
            # driver.execute_script('arguments[0].scrollIntoView(true);', driver.find_element(By.XPATH, f'//span[normalize-space()=\'{INPUT_DATA[-5]}\']'))

            driver.find_element(By.XPATH, f'//material-select-dropdown-item[@role=\'option\']//span[contains(text(),\'{INPUT_DATA[-5]}\')]').location_once_scrolled_into_view
            time.sleep(0.5)
            action.move_to_element(driver.find_element(By.XPATH, f'//material-select-dropdown-item[@role=\'option\']//span[contains(text(),\'{INPUT_DATA[-5]}\')]'))
            action.click().perform()

        except Exception as e:
            DEBUG_FILE.write(
                "error selecting category" + '\n========================================================\n')

        # select tags
        try:
            # click manage tags
            driver.find_element(By.XPATH, '//div[contains(text(),\'Manage tags\')]').click()
            WebDriverWait(driver, 60).until(EC.presence_of_element_located(
                (By.XPATH, '//body/div[@name=\'default\']/div/div/focus-trap/div/relative-popup['
                           '@is-navigation-drawer-open=\'false\']/div[@aria-hidden=\'false\']/span/div['
                           '@role=\'dialog\']/div[1]/div[1]')))
            # select tags
            counter = 0
            for tag in INPUT_DATA[-4].split(','):
                if tag == '':
                    continue
                if counter > 5:
                    break
                counter += 1
                # driver.find_element(By.XPATH, f'//span[normalize-space()=\'{tag}\']').location_once_scrolled_into_view
                driver.find_element(By.XPATH, '//input[@aria-label=\'Search tags\']').send_keys(tag)
                time.sleep(0.3)
                # driver.find_elements(By.XPATH, '//mat-checkbox[@aria-label=\'Select row\']//div//*[name()=\'svg\']')[0].click()
                # check the 6-ht tag if the query is "simulation"
                if (tag == "Simulation"):
                    driver.find_element(By.XPATH, '(//*[name()=\'svg\'])[9]').click()
                else:
                    driver.find_elements(By.XPATH, '//div[@class=\'mat-checkbox-container\']//*[name()=\'svg\']')[0].click()

                driver.find_element(By.XPATH, '//input[@aria-label=\'Search tags\']').clear()

            # click apply
            driver.find_element(By.XPATH, '//span[normalize-space()=\'Apply\']').click()
            time.sleep(3)

        except Exception as e:
            DEBUG_FILE.write(
                "error selecting tags" + '\n========================================================\n')

        # scroll to contact details
        driver.find_element(By.XPATH, '//div[contains(text(),\'Manage tags\')]').location_once_scrolled_into_view

        # fill contact details
        try:
            # fill email
            driver.find_element(By.XPATH, '//console-section[@htmltitle=\'Store listing contact details\']//div['
                                          '@aria-label=\'Email address\']//div//div//input['
                                          '@type=\'text\']').send_keys(INPUT_DATA[-3])
            # fill website
            driver.find_element(By.XPATH, '//console-section[@htmltitle=\'Store listing contact details\']//div['
                                          '@aria-label=\'Website\']//div//div//input').send_keys(INPUT_DATA[-2])
        except Exception as e:
            DEBUG_FILE.write(
                "error filling contact details" + '\n========================================================\n')

        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save\']').click()
        WebDriverWait(driver, 60).until(
            EC.text_to_be_present_in_element((By.XPATH, '//*[@id="main-content"]/div/div['
                                                        '1]/page-router-outlet/page-wrapper/div/store-settings-page'
                                                        '/form-bottom-bar/bottom-bar-base/div/div/div/div[1]/span'),
                                             'Your changes have been saved'))
        return True

    except Exception as e:
        DEBUG_FILE.write(
            "error filling store settings section" + '\n========================================================\n')


def fill_production_section():
    try:
        action = ActionChains(driver)
        driver.get(URL + APP_ID + 'tracks/production?tab=countryAvailability')
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(EC.presence_of_element_located(
            (By.XPATH, '//div[normalize-space()=\'Add countries / regions\']')))

        # click add country
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Add countries / regions\']').click()
        WebDriverWait(driver, 60).until(EC.visibility_of_element_located(
            (By.XPATH, '//input[@aria-label=\'Search countries / regions\']')))
        # select all
        action.scroll_to_element(driver.find_element(By.XPATH, '//mat-checkbox[@aria-label=\'Select all rows\']'))
        action.perform()
        time.sleep(0.3)
        action.move_to_element(driver.find_element(By.XPATH, '//mat-checkbox[@aria-label=\'Select all rows\']'))
        action.click().perform()
        time.sleep(0.3)
        # click add country / region
        action.move_to_element(driver.find_element(By.XPATH, '//material-button[@debug-id=\'overlay-confirm-button'
                                                             '\']//material-ripple[@aria-hidden=\'true\']'))
        action.click().perform()
        WebDriverWait(driver, 60).until(EC.visibility_of_element_located(
            (By.XPATH, '//div[contains(text(),\'Your app will be available on Google Play to users\')]')))
        # click add
        time.sleep(0.3)
        action.move_to_element(driver.find_element(By.XPATH, '//*[@id="default-acx-overlay-container"]/div['
                                                             '3]/material-dialog/focus-trap/div['
                                                             '2]/div/footer/div/div/console-button-set/div/button[2]'))
        action.click().perform()
        WebDriverWait(driver, 60).until(EC.visibility_of_element_located(
            (By.XPATH, '//body[1]/div[1]/root[1]/console-chrome[1]/div[1]/div[1]/div[1]/div[1]/div['
                       '1]/page-router-outlet[1]/page-wrapper[1]/div[1]/track-page[1]/div[1]/country-availability['
                       '1]/console-section[1]/div[1]/div[1]/countries-table[1]/console-block-1-column[1]/div[1]/div['
                       '1]/console-table[1]/div[1]/div[1]/ess-table[1]/ess-particle-table[1]/div[1]/div[1]/div['
                       '2]/div[2]/ess-cell[2]/console-table-text-cell[1]/div[1]/div[1]/span[2]')))

        # click Create new release
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Create new release\']').click()
        # wait for page to be loaded
        WebDriverWait(driver, 120).until(EC.visibility_of_element_located(
            (By.XPATH, '//span[normalize-space()=\'App bundles\']')))
        # upload file and wait 300 sec
        driver.find_element(By.XPATH, '//input[@accept=\'.aab\']').send_keys(release_dir)
        time.sleep(2)
        WebDriverWait(driver, 400).until(EC.element_to_be_clickable((By.XPATH, '//*[@id="main-content"]/div/div['
                                                                               '1]/page-router-outlet/page-wrapper'
                                                                               '/div/app-releases-prepare-page'
                                                                               '/console-section['
                                                                               '2]/div/div/console-block-1-column/div'
                                                                               '/div/form-bottom-bar/bottom-bar-base'
                                                                               '/div/div/div/div['
                                                                               '2]/console-button-set/div/material'
                                                                               '-button[2]/button')))
        # click save
        driver.find_element(By.XPATH, '//div[normalize-space()=\'Save as draft\']').click()
        time.sleep(8)
        return True

    except Exception as e:
        DEBUG_FILE.write(
            "error while filling production section" + '\n========================================================\n')
        return False


# create new app section by section
def create_new_app():
    global driver, DEBUG_FILE
    try:
        driver.get(URL + 'create-new-app')
        # mandatory functions to continue
        # fill the first form
        if not fill_main_form():
            DEBUG_FILE.write(
                "error while filling the main form" + '\n========================================================\n')
            return False
        # try to fill the rest
        try:
            # not mandatory functions
            if not fill_app_content_section():
                DEBUG_FILE.write(
                    "App content section isn't completed" + '\n========================================================\n')

            if not fill_main_store_listing_section():
                DEBUG_FILE.write(
                    "main store listing section isn't completed" + '\n========================================================\n')
            if not fill_store_settings_section():
                DEBUG_FILE.write(
                    "store settings section isn't completed" + '\n========================================================\n')
            if not fill_production_section():
                DEBUG_FILE.write(
                    "production section isn't completed" + '\n========================================================\n')
            return True

        except Exception as e:
            DEBUG_FILE.write(str(e) + '\n========================================================\n')
            return False

    except Exception as e:
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        return False


def main():
    global URL
    try:
        # read data from txt file
        if not get_data_file():
            print('reading data failed\n')
            return False
        # read url from txt file
        URL = INPUT_DATA[-1].strip()
        # open browser and connect to driver
        if not open_browser_and_driver():
            print('open_browser_and_driver() failed\n')
            return False
        # open google console and sign in if needed
        if not open_google_console():
            print('open_google_console() failed\n')
            return False
        # create new app
        if not create_new_app():
            print('create_new_app() failed\n')
            return False

        return True

    except Exception as e:
        DEBUG_FILE.write(str(e) + '\n========================================================\n')
        return False


if __name__ == '__main__':
    main()
    os.system('pause')
    driver.quit()
    DEBUG_FILE.close()

