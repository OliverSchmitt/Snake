#define WINDOW_TITLE "Snake"
#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 720
#define LEVEL_WIDTH 22
#define LEVEL_HEIGHT 22
#define TILE_WIDTH WINDOW_WIDTH/(LEVEL_WIDTH + 2)
#define TILE_HEIGHT WINDOW_HEIGHT/(LEVEL_HEIGHT + 2)

#define BASE_PATH ".."

#define HEAD_PATH BASE_PATH "/assets/head30.png"
#define BODY_PATH BASE_PATH "/assets/body30.png"
#define TAIL_PATH BASE_PATH "/assets/tail30.png"
#define WALL_PATH BASE_PATH "/assets/wall30.png"
#define FRUIT_PATH BASE_PATH "/assets/fruit30.png"

#define FONT_PATH BASE_PATH "/fonts/zillm/ZILLM___.ttf"
#define FONT_SIZE 30
#define TEXT_WIDTH 400

#define SCORE_TEXT "SCORE"
#define SCORE_X 0
#define SCORE_Y 0
#define CURRENT_SCORE_X 60
#define CURRENT_SCORE_Y 0

#define START_TEXT "USE W,A,S,D OR THE ARROW\nKEYS TO MOVE THE SNAKE"
#define START_X 225
#define START_Y 200

#define DIED_TEXT "YOU DIED!"
#define DIED_X 225
#define DIED_Y 200

#define REACHED_TEXT "YOU REACHED A SCORE OF"
#define REACHED_X 225
#define REACHED_Y 230

#define AFTER_SCORE_X 225
#define AFTER_SCORE_Y 230

#define RECORD_WAS_TEXT "THE RECORD WAS"
#define RECORD_WAS_X 250
#define RECORD_WAS_Y 260

#define AFTER_RECORD_X 225
#define AFTER_RECORD_Y 260

#define AGAIN_TEXT "DO YOU WANT TO PLAY AGAIN?"
#define AGAIN_X 225
#define AGAIN_Y 290

#define YES_TEXT "[Y]ES"
#define YES_Y 320
#define NO_TEXT "[N]O"
#define NO_Y 320
#define YES_NO_OFFSET 70

#define RECORD_TEXT "RECORD"
#define RECORD_X 240
#define RECORD_Y 0
#define CURRENT_RECORD_X 310
#define CURRENT_RECORD_Y 0

#define BAR_PATH BASE_PATH "/assets/bar.png"
#define BAR_BORDER_PATH BASE_PATH "/assets/barBorder.png"
#define BAR_X 120
#define BAR_Y 5
#define BAR_WIDTH 100
#define BAR_HEIGHT 20

#define RENDER_DELAY 100

#define SCORE_FILE_NAME BASE_PATH "/stats/score.txt"
