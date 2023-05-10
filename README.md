# automate_google_play_console

## automate adding new app in the google play console using python selenium and c++ WinForms.

- code snippet from sendGooglePlayData.py

```

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

```
