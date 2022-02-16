#include <sstream>
#include "game.hpp"

#include "adult_cockroach.h"
#include "child_cockroach.h"
#include "mother_cockroach.h"

#include "tower.h"
#include "basic_tower.h"
#include "machine_gun_tower.h"
#include "shotgun_tower.h"

#include "build_machine_gun_tower_icon.hpp"
#include "build_shotgun_tower_icon.hpp"

#include "item_placeble_tile.h"
#include "item_not_placeble_tile.h"

/**
 * @brief Construct a new Game:: Game object
 *
 * @param tile_width     Tile width for the game view
 * @param tile_height    Tile height for the game view
 * @param player_balance Player balance at the start
 * return None
*/
Game::Game(int tile_width, int tile_height, int player_balance) : tile_width_(tile_width), tile_height_(tile_height), QGraphicsView(), Wallet(player_balance)
{
    // set cursor to nullptr
    InitializeGameMaplayout();
    InitializeLevelInfo();

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 13 * tile_width, 9 * tile_width);
    setFixedSize(13 * tile_width, 9 * tile_height);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    cursor = nullptr;
    building = nullptr;
    setMouseTracking(true);
    WaveCompleteMsgBox = new QMessageBox();
    GameOverMsgBox = new QMessageBox();
    LevelCompleteMsgBox = new QMessageBox();

    BalanceUpdateTimer = new QTimer();

    CreateNewLevel();
    connect(BalanceUpdateTimer, SIGNAL(timeout()), this, SLOT(UpdateBalance()));
    BalanceUpdateTimer->start(100);

    connect(WaveCompleteMsgBox, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(WaveComplete()));
    connect(this, SIGNAL(StartNextWave()), this, SLOT(WaitForPlayer()));
    connect(this, SIGNAL(GameOver()), this, SLOT(ResetLevel()));
    connect(LevelCompleteMsgBox, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(CreateNewLevel()));
    connect(GameOverMsgBox, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(WaitForPlayer()));
}
/**
 * @brief Destroy the Game:: Game object
 *
 */
Game::~Game()
{
}

/**
 * @brief Intialize Game level map layout and store then
 * into a vector
 *
 * @brief Create Map layout list
 * @param None
 * @return None
 */
void Game::InitializeGameMaplayout()
{
    std::vector<std::vector<int>> map_layout_template{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    std::vector<std::vector<int>> map_layout_1{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {R, R, R, G, R, R, R, G, R, R, R, G, G},
        {G, G, R, G, R, G, R, G, R, G, R, G, G},
        {G, G, R, G, R, G, R, G, R, G, R, G, G},
        {G, G, R, G, R, G, R, G, R, G, R, G, G},
        {G, G, R, G, R, G, R, G, R, G, R, G, G},
        {G, G, R, R, R, G, R, R, R, G, R, R, X},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    std::vector<std::vector<int>> map_layout_2{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {R, R, G, G, G, G, G, G, G, R, R, R, X},
        {G, R, G, R, R, R, R, R, G, R, G, G, G},
        {G, R, G, R, G, G, G, R, G, R, G, G, G},
        {G, R, G, R, G, G, G, R, G, R, G, G, G},
        {G, R, G, R, G, G, G, R, G, R, G, G, G},
        {G, R, R, R, G, G, G, R, R, R, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    std::vector<std::vector<int>> map_layout_3{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, R, R, R, G, G, G, G, G},
        {G, G, G, G, G, R, G, R, G, G, G, G, G},
        {G, G, G, G, G, R, G, R, G, G, G, G, G},
        {G, R, R, R, G, R, G, R, R, R, R, R, X},
        {G, R, G, R, G, R, G, G, G, G, G, G, G},
        {R, R, G, R, R, R, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    std::vector<std::vector<int>> map_layout_4{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {R, R, R, R, G, G, G, G, G, G, G, G, G},
        {G, G, G, R, G, G, G, G, G, G, G, G, G},
        {G, G, G, R, R, R, G, G, G, G, G, G, G},
        {G, G, G, G, G, R, G, G, G, G, G, G, G},
        {G, G, G, G, G, R, R, R, R, R, G, G, G},
        {G, G, G, G, G, G, G, G, G, R, G, G, G},
        {G, G, G, G, G, G, G, G, G, R, R, R, X},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    std::vector<std::vector<int>> map_layout_5{
        {B, S, M, A, A, A, A, A, A, A, E, W, D},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, R, R, R, R, G, R, R, R, G, G, G},
        {G, G, R, G, G, R, G, R, G, R, R, R, X},
        {G, G, R, G, G, R, R, R, G, G, G, G, G},
        {R, R, R, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
        {G, G, G, G, G, G, G, G, G, G, G, G, G},
    };

    game_level_map_layouts_.push_back(map_layout_1);
    game_level_map_layouts_.push_back(map_layout_2);
    game_level_map_layouts_.push_back(map_layout_3);
    game_level_map_layouts_.push_back(map_layout_4);
    game_level_map_layouts_.push_back(map_layout_5);
}

/**
 * @brief Initialize Game level information based on a
 * vector each row contains the data for enemies in each wave
 * in the level. The data is formed in the following order:
 * number of child spawned, number of adult spawned,
 * number of mother spawned, enemy spawn interval
 *
 * @brief Define level information
 * @param None
 * @return None
 */
void Game::InitializeLevelInfo()
{
    std::vector<std::vector<int>> level_info_1{
        {5, 0, 0, 1000},
        {8, 0, 0, 1000},
        {8, 3, 0, 1000},
        {8, 3, 1, 1000},
        {10, 5, 2, 1000}};
    std::vector<std::vector<int>> level_info_2{
        {5, 0, 0, 2000},
        {8, 3, 0, 2000},
        {0, 3, 4, 1000},
        {0, 0, 8, 1000},
        {5, 10, 8, 1000}};
    std::vector<std::vector<int>> level_info_3{
        {5, 0, 0, 1000},
        {8, 0, 0, 1000},
        {0, 3, 2, 1000},
        {20, 0, 0, 500},
        {5, 10, 6, 1000}};
    std::vector<std::vector<int>> level_info_4{
        {5, 0, 0, 1000},
        {8, 0, 0, 500},
        {0, 6, 0, 500},
        {0, 15, 5, 500},
        {0, 0, 12, 1000}};
    std::vector<std::vector<int>> level_info_5{
        {5, 0, 0, 500},
        {0, 2, 1, 1000},
        {0, 10, 0, 500},
        {20, 0, 2, 500},
        {0, 0, 20, 300}};

    levels_.push_back(level_info_1);
    levels_.push_back(level_info_2);
    levels_.push_back(level_info_3);
    levels_.push_back(level_info_4);
    levels_.push_back(level_info_5);
}

/**
 * @brief Create map layout based on the current level
 *
 * @brief Create New game settings for user based on the current level 
 * @param None
 * @return None
 */
void Game::CreateNewLevel()
{
    wave_left_ = 5;
    map_info_.clear();
    enemy_path_.clear();

    switch (current_level_)
    {
        case 0:
        {
            start_balance_ = GetBalance();
            BuildMap(game_level_map_layouts_[0]);
            GenerateEnemyPath(0, 2);
            break;
        }
        case 1:
        {
            SetNewBalance(150);
            start_balance_ = 150;
            scene->clear();
            BuildMap(game_level_map_layouts_[1]);
            GenerateEnemyPath(0, 2);
            break;
        }
        case 2:
        {
            SetNewBalance(200);
            start_balance_ = 200;
            scene->clear();
            BuildMap(game_level_map_layouts_[2]);
            GenerateEnemyPath(0, 7);
            break;
        }
        case 3:
        {
            SetNewBalance(250);
            start_balance_ = 200;
            scene->clear();
            BuildMap(game_level_map_layouts_[3]);
            GenerateEnemyPath(0, 1);
            break;
        }
        case 4:
        {
            SetNewBalance(300);
            start_balance_ = 200;
            scene->clear();
            BuildMap(game_level_map_layouts_[4]);
            GenerateEnemyPath(0, 6);
            break;
        }
        case 5:
        {
            SetNewBalance(300);
            start_balance_ = 200;
            current_level_ = 0;
            LevelCompleteMsgBox->setText("Congrats you saved your home :D! Play again?");
            LevelCompleteMsgBox->show();
        }
    }

    connect(done_button, SIGNAL(clicked()), this, SLOT(StartWave()));
}

/**
 * @brief Slot updating player balance in game view
 *
 * @brief Check user banking balance again
 * @param None
 * @return None
 */
void Game::UpdateBalance()
{
    CurrentBalanceText->setPlainText(QString::number(GetBalance()));
}

/**
 * @brief Slot starting the wave and creating
 * the enemies
 *
 * @brief Create numbers of enemies
 * @param None
 * @return None
 */
void Game::StartWave()
{
    std::vector<int> config = levels_[current_level_][current_wave_];
    createEnemies(config[0], config[1], config[2], config[3]);
    done_button->setDisabled(true);
}

/**
 * @brief Create enemies and set their spawn time
 *
 * @param child_ammount     Number of child cockroached to spawn
 * @param adult_ammount     Number of adult cockroached to spawn
 * @param mother_ammount    Number of mother cockroached to spawn
 * @param interval          Interval for cockroach spawn
 *
 * @return NONE
 */
void Game::createEnemies(int child_ammount, int adult_ammount, int mother_ammount, int interval)
{
    SpawnChildTimer = new QTimer(this);
    SpawnAdultTimer = new QTimer(this);
    SpawnMotherTimer = new QTimer(this);
    WaveCheckTimer = new QTimer(this);

    child_spawmed = child_ammount;
    adult_spawmed = adult_ammount;
    mother_spawmed = mother_ammount;
    child_killed = 0;
    adult_killed = 0;
    mother_killed = 0;
    total_spawned = child_ammount + adult_ammount + mother_ammount + (mother_ammount * 4);

    if (child_spawmed > 0)
    {
        connect(SpawnChildTimer, SIGNAL(timeout()), this, SLOT(SpawnChild()));
        SpawnChildTimer->start(interval);
    }

    if (adult_spawmed > 0)
    {
        connect(SpawnAdultTimer, SIGNAL(timeout()), this, SLOT(SpawnAdult()));
        SpawnAdultTimer->start(interval);
    }

    if (mother_spawmed > 0)
    {

        connect(SpawnMotherTimer, SIGNAL(timeout()), this, SLOT(SpawnMother()));
        SpawnMotherTimer->start(interval);
    }

    connect(WaveCheckTimer, SIGNAL(timeout()), this, SLOT(IsWaveComplete()));
    WaveCheckTimer->start(500);
}

/**
 * @brief Slot for checking if the current wave is complete
 *
 * @brief Check if all enemies were killed or not
 * @param None
 * @return None
 */
void Game::IsWaveComplete()
{
    int killed = child_killed + adult_killed + mother_killed;

    if (game_over_flag == true)
    {
        WaveCheckTimer->disconnect();
        emit GameOver();
    }

    if (killed != total_spawned)
    {
        return;
    }

    if (current_wave_ < 4)
    {
        WaveCheckTimer->disconnect();
        wave_left_--;
        std::stringstream ss;
        ss << "Wave " << current_wave_ + 1 << " complete, " << wave_left_ << " waves left";
        WaveCompleteMsgBox->setText(QString::fromStdString(ss.str()));
        WaveCompleteMsgBox->show();
    }
    else
    {
        WaveCheckTimer->disconnect();
        qDebug() << "Level complete!!";
        current_level_++;
        std::stringstream ss;
        ss << "All " << current_wave_ + 1 << " complete, "
           << "Moving to level " << current_level_ + 1;
        LevelCompleteMsgBox->setText(QString::fromStdString(ss.str()));
        LevelCompleteMsgBox->show();
        current_wave_ = 0;
    }
}

/**
 * @brief Slot for handling when wave is complete
 *
 * @param None
 * @return None
 */
void Game::WaveComplete()
{
    done_button->setDisabled(false);
    current_wave_++;
    done_button->setText(QString("Start Level: " + QString::number(current_level_ + 1) + QString("\nwave: ") + QString::number(current_wave_ + 1)));
    emit StartNextWave();
}

/**
 * @brief Slot for Waiting for the player to start the wave again
 */
void Game::WaitForPlayer()
{
    done_button->setDisabled(false);
}

/**
 * @brief Waiting for player ot start the wave again
 */
void Game::ResetLevel()
{
    current_wave_ = 0;
    wave_left_ = 5;

    QList<QGraphicsItem *> items = scene->items();

    for (int i = 0; i < items.size(); i++)
    {
        Cockroach *enemy = dynamic_cast<Cockroach *>(items[i]);
        if (enemy)
        {
            scene->removeItem(enemy);
            delete enemy;
        }

        Tower *tower = dynamic_cast<Tower *>(items[i]);

        if (tower)
        {
            scene->removeItem(tower);
            delete tower;
        }
    }

    if (game_over_flag == true)
    {
        GameOverMsgBox->setText("Game over :(");
        GameOverMsgBox->show();
        SetNewBalance(start_balance_);
        game_over_flag = false;
    }
}

/**
 * @brief Build map based of an 2D vector
 * and also defines the tile infomation and their
 * mid points
 * @param map_layout Map layout for the game level
 *
 * @return None
 */
void Game::BuildMap(std::vector<std::vector<int>> &map_layout)
{
    int x_offset = 0;
    int y_offset = 0;
    int mid_x = 0;
    int mid_y = 0;

    QString tile_path[] = {
        ":/tiles/images/tile_1.png",
        ":/tiles/images/tile_2.png",
        ":/tiles/images/tile_3.png",
        ":/tiles/images/tile_4.png",
        ":/tiles/images/tile_5.png",
        ":/tiles/images/tile_6.png",
        ":/tiles/images/tile_7.png",
        ":/tiles/images/tile_8.png",
    };

    std::vector<std::pair<int, QPointF>> row_info;

    for (auto &row : map_layout)
    {
        for (auto tile_type : row)
        {

            mid_x = x() + x_offset + (tile_width_ / 2);
            mid_y = y() + y_offset + (tile_height_ / 2);

            switch (tile_type)
            {
            case G:
            {
                int tile_num = rand() % 8;
                ItemPlacebleTile *tile = new ItemPlacebleTile(tile_path[tile_num], tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);
                break;
            }
            case R:
            {
                ItemNotPlacebleTile *tile = new ItemNotPlacebleTile(":/tiles/images/road_tile.png", tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);
                break;
            }
            case A:
            {
                ItemNotPlacebleTile *tile = new ItemNotPlacebleTile(":/tiles/images/shop_tile.png", tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);
                break;
            }
            case B:
            {
                QPixmap tile_img = QPixmap(":/icon/images/basic_gun_icon_tile.png");
                QPixmap tile_img_scaled = tile_img.scaled(tile_width_, tile_height_);
                basic_tower_icon = new BuildBasicTowerIcon();
                basic_tower_icon->setPixmap(tile_img_scaled);
                basic_tower_icon->setPos(x() + x_offset, y() + y_offset);
                scene->addItem(basic_tower_icon);

                break;
            }
            case M:
            {
                QPixmap tile_img = QPixmap(":/icon/images/machine_gun_icon_tile.png");
                QPixmap tile_img_scaled = tile_img.scaled(tile_width_, tile_height_);
                machine_gun_tower_icon = new BuildMachineGunTowerIcon();
                machine_gun_tower_icon->setPixmap(tile_img_scaled);
                machine_gun_tower_icon->setPos(x() + x_offset, y() + y_offset);
                scene->addItem(machine_gun_tower_icon);

                break;
            }
            case S:
            {
                QPixmap tile_img = QPixmap(":/icon/images/shotgun_gun_icon_tile.png");
                QPixmap tile_img_scaled = tile_img.scaled(tile_width_, tile_height_);
                shotgun_tower_icon = new BuildShotgunTowerIcon();
                shotgun_tower_icon->setPixmap(tile_img_scaled);
                shotgun_tower_icon->setPos(x() + x_offset, y() + y_offset);
                scene->addItem(shotgun_tower_icon);
                break;
            }
            case E:
            {
                ItemNotPlacebleTile *tile = new ItemNotPlacebleTile(":/icon/images/elon_icon_tile.png", tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);
                break;
            }
            case W:
            {
                ItemNotPlacebleTile *tile = new ItemNotPlacebleTile(":/tiles/images/wallet_tile.png", tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);

                QFont font;
                font.setPointSize(20);
                font.setBold(true);

                CurrentBalanceText = new QGraphicsTextItem();
                CurrentBalanceText->setFont(font);
                CurrentBalanceText->setPlainText(QString::number(GetBalance()));
                CurrentBalanceText->setPos(mid_x - 26, mid_y - 20);

                scene->addItem(CurrentBalanceText);
                break;
            }
            case D:
            {
                done_button = new QPushButton();
                done_button->setText(QString("Start Level: " + QString::number(current_level_ + 1) + QString("\nwave: ") + QString::number(current_wave_ + 1)));
                done_button->setGeometry(x() + x_offset, y() + y_offset, tile_width_, tile_height_);
                scene->addWidget(done_button);
                break;
            }
            case X:
            {

                ItemNotPlacebleTile *tile = new ItemNotPlacebleTile(":/tiles/images/entrance_tile.png", tile_width_, tile_height_, QPointF(x() + x_offset, y() + y_offset));
                scene->addItem(tile);
                break;
            }
            default:
                qDebug() << "Unknown tile type: " << tile_type;
                break;
            }

            row_info.push_back(std::make_pair(tile_type, QPointF(mid_x, mid_y)));
            x_offset += tile_width_;
        }

        // Reset x offset and increment y_offset down by height of tile
        x_offset = 0;
        y_offset += tile_height_;
        map_info_.push_back(row_info);
        row_info.clear();
    }

    setScene(scene);
}

/**
 * @brief Genrate enemy path by reading map information
 *
 * @param start_cell_x_pos   x postion of cell in the map
 * @param start_cell_y_pos   y postion of cell in the map
 *
 * @return None
 *
 */
void Game::GenerateEnemyPath(int start_cell_x_pos, int start_cell_y_pos)
{
    int curr_x = start_cell_x_pos;
    int curr_y = start_cell_y_pos;
    int mid_x = (start_cell_x_pos * tile_width_) + tile_width_ / 2;
    int mid_y = (start_cell_y_pos * tile_height_) + tile_height_ / 2;

    QPointF start(mid_x, mid_y);
    QPointF current = start;
    QPointF prev = start;

    int row_index = map_info_[0].size();
    int col_index = map_info_.size();
    enemy_path_.push_back(current);

    while (true)
    {
        if (curr_x + 1 <= row_index && (map_info_[curr_y][curr_x + 1].first == R || map_info_[curr_y][curr_x + 1].first == X) && map_info_[curr_y][curr_x + 1].second != prev)
        {
            prev = current;
            current = map_info_[curr_y][curr_x + 1].second;
            enemy_path_.push_back(current);
            curr_x += 1;
        }
        else if (curr_y + 1 < col_index && (map_info_[curr_y + 1][curr_x].first == R || map_info_[curr_y + 1][curr_x].first == X) && map_info_[curr_y + 1][curr_x].second != prev)
        {
            prev = current;
            current = map_info_[curr_y + 1][curr_x].second;
            enemy_path_.push_back(current);
            curr_y += 1;
        }
        else if (curr_y - 1 > 0 && (map_info_[curr_y - 1][curr_x].first == R || map_info_[curr_y - 1][curr_x].first == X) && map_info_[curr_y - 1][curr_x].second != prev)
        {
            prev = current;
            current = map_info_[curr_y - 1][curr_x].second;
            enemy_path_.push_back(current);
            curr_y -= 1;
        }
        else if (curr_x - 1 > 0 && (map_info_[curr_y][curr_x - 1].first == R || map_info_[curr_y][curr_x - 1].first == X) && map_info_[curr_y][curr_x - 1].second != prev)
        {

            prev = current;
            current = map_info_[curr_y][curr_x - 1].second;
            enemy_path_.push_back(current);
            curr_y -= 1;
        }
        else
        {
            break;
        }
    }
}

/**
 * @brief Draw enemy path
 * Used for Debug purposes
 *
 * @param   path    Qlist of points/coordinates the enemy should follow
 *
 * @return None
 */
void Game::DrawEnemyPath(QList<QPointF> &path)
{
    QPainter draw_path;
    for (auto it = path.begin(); it != path.end(); it++)
    {
        auto next = std::next(it);

        if (next != path.end())
        {
            QLineF line(*it, *next);
            QGraphicsLineItem *lineItem = new QGraphicsLineItem(line);

            QPen pen;
            pen.setWidth(10);
            pen.setColor(Qt::black);

            lineItem->setPen(pen);
            scene->addItem(lineItem);
        }
    }
}

/**
 * @brief Change the cursor to the picture given as parameter
 *
 * @param filename  points to the filename
 *
 * @return None
 *
 */
void Game::setCursor(QString filename)
{
    cursor = new QGraphicsPixmapItem();
    QPixmap pix = QPixmap(filename);
    QPixmap pix_scaled = pix.scaled(50, 50);
    cursor->setPixmap(pix_scaled);
    scene->addItem(cursor);
}

/**
 * @brief Cursor follows the mouse
 *
 * @param event     tracks the position of mouse movement
 *
 * @return None
 *
 */
void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor)
    {
        cursor->setPos(event->pos());
    }
}

/**
 * @brief Tracks the items pressed by the mouse
 *
 * @param event     tracks the position of mouse movement
 *
 * @return None
 *
 */
// Use different name here
void Game::mousePressEvent(QMouseEvent *event)
{
    if (building)
    {
        // return if the cursor is colliding with the tower
        QList<QGraphicsItem *> items = cursor->collidingItems();
        for (size_t i = 0, n = items.size(); i < n; i++)
        {
            if (dynamic_cast<Tower *>(items[i]))
            {
                return;
            }

            if (dynamic_cast<ItemNotPlacebleTile *>(items[i]))
            {
                return;
            }

            if(dynamic_cast<BuildBasicTowerIcon *>(items[i]))
            {
                return;
            }

            if(dynamic_cast<BuildMachineGunTowerIcon *>(items[i]))
            {
                return;
            }

            if(dynamic_cast<BuildShotgunTowerIcon *>(items[i]))
            {
                return;
            }
        }

        // otherwise build at the clicked location
        scene->addItem(building);
        building->setPos(event->pos());
        scene->removeItem(cursor);
        cursor = nullptr;
        building = nullptr;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

/**
 * @brief Slot for spawning child cockroaches
 * @param NONE
 * @return NONE
 *
 */
void Game::SpawnChild()
{
    Child_cockroach *enemy = new Child_cockroach(100, 14, 15, enemy_path_, 0, QPoint(0, 0));
    scene->addItem(enemy);
    child_spawmed -= 1;

    if (child_spawmed == 0)
    {
        SpawnChildTimer->disconnect();
    }
}

/**
 * @brief Slot for spawning adult cockroaches
 * @param NONE
 * @return NONE
 */
void Game::SpawnAdult()
{
    Adult_cockroach *enemy = new Adult_cockroach(300, 14, 20, enemy_path_);
    scene->addItem(enemy);
    adult_spawmed -= 1;

    if (adult_spawmed == 0)
    {
        SpawnAdultTimer->disconnect();
    }
}

/**
 * @brief Slot for spawning mother cockroaches
 * @param NONE
 * @return NONE
 */
void Game::SpawnMother()
{
    Mother_cockroach *enemy = new Mother_cockroach(200, 7, 30, 20, 14, 15, enemy_path_);
    scene->addItem(enemy);
    mother_spawmed -= 1;

    if (mother_spawmed == 0)
    {
        SpawnMotherTimer->disconnect();
    }
}
