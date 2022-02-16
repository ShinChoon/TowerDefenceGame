#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QColor>
#include <QObject>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QGraphicsTextItem>


#include "tower.h"
#include "wallet.hpp"
#include "build_basic_tower_icon.hpp"
#include "build_machine_gun_tower_icon.hpp"
#include "build_shotgun_tower_icon.hpp"

// #include <queue>

#define G 1  /** Ground tile*/
#define R 2  /** Road tile */
#define A 3  /** Shop tile*/
#define B 4  /** Basic tower tile */
#define M 5  /** Machine gun tower tile */
#define S 6  /** Machine gun tower tile */
#define E 7  /** Elon icon tile */
#define W 8  /** Wallet icon tile */
#define D 9  /** Done button tile */
#define X 10 /** Exit tile */
#define L 11 /** Currnent Level info tile */
#define C 12 /** Current wave info tile */


class Game : public QGraphicsView, public Wallet
{
    Q_OBJECT
public:
    Game(int tile_width, int tile_height, int player_balance);
    ~Game();

    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem *cursor;
    Tower *building;
    QTimer *SpawnChildTimer;
    QTimer *SpawnAdultTimer;
    QTimer *SpawnMotherTimer;
    QTimer *WaveCheckTimer;
    QTimer *BalanceUpdateTimer;
    QList<QPointF> pointsToFollow;
    QPushButton *done_button;
    QMessageBox *WaveCompleteMsgBox;
    QMessageBox *GameOverMsgBox;
    QMessageBox *LevelCompleteMsgBox;
    QGraphicsTextItem *CurrentBalanceText;

    BuildBasicTowerIcon *basic_tower_icon;
    BuildMachineGunTowerIcon *machine_gun_tower_icon;
    BuildShotgunTowerIcon *shotgun_tower_icon;

    int child_killed;
    int adult_killed;
    int mother_killed;

    int child_spawmed;
    int adult_spawmed;
    int mother_spawmed;
    int spawn_interval;
    int total_spawned;

    bool game_over_flag = false;
    void createEnemies(int child_ammount, int adult_ammount, int mother_ammount, int interval);
    void setCursor(QString filename);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void LevelTwo();

public slots:
//    void spawnEnemy();
    void SpawnChild();
    void SpawnAdult();
    void SpawnMother();

    void StartWave();
    void IsWaveComplete();
    void WaveComplete();
    void WaitForPlayer();
    void ResetLevel();
    void CreateNewLevel();
    void UpdateBalance();

signals:
    void StartNextWave(void);
    void GameOver(void);

private:
    QList<QPointF> enemy_path_;
    std::vector<std::vector<std::pair<int, QPointF>>> map_info_;
    std::vector<std::vector<std::vector<int>>> game_level_map_layouts_;
    std::vector<std::vector<std::vector<int>>> levels_;
    int current_wave_ = 0;
    int current_level_ = 0;
    int wave_left_ = 5;
    int tile_width_;
    int tile_height_;
    int start_balance_;

    void BuildMap(std::vector<std::vector<int>> &map_layout);
    void GenerateEnemyPath(int start_cell_x_pos, int start_cell_y_pos);
    void DrawEnemyPath(QList<QPointF> &path);
    void InitializeGameMaplayout();
    void InitializeLevelInfo();
};

#endif //GAME_H
