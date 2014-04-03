/**
***  BVH動作フ?イルの読み込み・再生のサンプルプログラ?
***  Copyright (c) 2004-2007, Masaki OSHITA (www.oshita-lab.org)
**/


#ifdef  WIN32
    #include <windows.h>
#endif

#include <GL/glut.h>

#include "BVH.h"


//
//  カメラ・GLUTの入力処理に関するグロ?バル変数
//

// カメラの回?のための変数
static float   camera_yaw = 0.0f;      // Ｙ軸を中心とする回?角度
static float   camera_pitch = -20.0f;  // Ｘ軸を中心とする回?角度
static float   camera_distance = 5.0f; // 中心からカメラの距離

// ?ウスのドラッグのための変数
static int     drag_mouse_r = 0; // 右??ンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     drag_mouse_l = 0; // 左??ンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     drag_mouse_m = 0; // 中??ンがドラッグ中かどうかのフラグ（1:ドラッグ中, 0:非ドラッグ中）
static int     last_mouse_x, last_mouse_y; // 最後に記?された?ウスカ??ルの座標

// ウィンドウのサイズ
static int     win_width, win_height;


//
//  アニメ?ション関連のグロ?バル変数
//

// アニメ?ション中かどうかを?すフラグ
bool   on_animation = true;

// アニメ?ションの再生時間
float  animation_time = 0.0f;

// 現在の?示フレ??番号
int    frame_no = 0;

// BVH動作デ??
BVH *   bvh = NULL;



//
//  テキストを?画
//
void  drawMessage( int line_no, const char * message )
{
    int   i;
    if ( message == NULL )
        return;

    // 射影行列を初期化（初期化の前に現在の行列を退避）
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D( 0.0, win_width, win_height, 0.0 );

    // モデルビュ?行列を初期化（初期化の前に現在の行列を退避）
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();

    // Ｚバッフ?・ライティングはオフにする
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

    // メッセ?ジの?画
    glColor3f( 1.0, 0.0, 0.0 );
    glRasterPos2i( 8, 24 + 18 * line_no );
    for ( i=0; message[i]!='\0'; i++ )
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, message[i] );

    // 設定を全て復元
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_LIGHTING );
    glMatrixMode( GL_PROJECTION );
    glPopMatrix();
    glMatrixMode( GL_MODELVIEW );
    glPopMatrix();
}


//
//  ウィンドウ再?画時に呼ばれるコ?ルバック関数
//
void  display( void )
{
    // 画面をクリア
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

    // 変換行列を設定（モデル座標系→カメラ座標系）
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, - camera_distance );
    glRotatef( - camera_pitch, 1.0, 0.0, 0.0 );
    glRotatef( - camera_yaw, 0.0, 1.0, 0.0 );
    glTranslatef( 0.0, -0.5, 0.0 );

    // 光源位置を再設定
    float  light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light0_position );

    // 地面を?画
    float  size = 1.5f;
    int  num_x = 10, num_z = 10;
    double  ox, oz;
    glBegin( GL_QUADS );
        glNormal3d( 0.0, 1.0, 0.0 );
        ox = -(num_x * size) / 2;
        for ( int x=0; x<num_x; x++, ox+=size )
        {
            oz = -(num_z * size) / 2;
            for ( int z=0; z<num_z; z++, oz+=size )
            {
                if ( ((x + z) % 2) == 0 )
                    glColor3f( 1.0, 1.0, 1.0 );
                else
                    glColor3f( 0.8, 0.8, 0.8 );
                glVertex3d( ox, 0.0, oz );
                glVertex3d( ox, 0.0, oz+size );
                glVertex3d( ox+size, 0.0, oz+size );
                glVertex3d( ox+size, 0.0, oz );
            }
        }
    glEnd();

    // キャラク?を?画
    glColor3f( 1.0f, 0.0f, 0.0f );
    if ( bvh )
        bvh->RenderFigure( frame_no, 0.02f );

    // 時間とフレ??番号を?示
    char  message[ 64 ];
    if ( bvh )
        sprintf( message, "%.2f (%d)", animation_time, frame_no );
    else
        sprintf( message, "Press 'L' key to Load a BVH file" );
    drawMessage( 0, message );

    // バックバッフ?に?画した画面をフロントバッフ?に?示
    glutSwapBuffers();
}


//
//  ウィンドウサイズ変更時に呼ばれるコ?ルバック関数
//
void  reshape( int w, int h )
{
    // ウィンドウ内の?画を行う範囲を設定（ここではウィンドウ全体に?画）
    glViewport(0, 0, w, h);
    
    // カメラ座標系→スクリ?ン座標系への変換行列を設定
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45, (double)w/h, 1, 500 );

    // ウィンドウのサイズを記?（テキスト?画処理のため）
    win_width = w;
    win_height = h;
}


//
// ?ウスクリック時に呼ばれるコ?ルバック関数
//
void  mouse( int button, int state, int mx, int my )
{
    // 左??ンが押されたらドラッグ開始
    if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_DOWN ) )
        drag_mouse_l = 1;
    // 左??ンが離されたらドラッグ終了
    else if ( ( button == GLUT_LEFT_BUTTON ) && ( state == GLUT_UP ) )
        drag_mouse_l = 0;

    // 右??ンが押されたらドラッグ開始
    if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_DOWN ) )
        drag_mouse_r = 1;
    // 右??ンが離されたらドラッグ終了
    else if ( ( button == GLUT_RIGHT_BUTTON ) && ( state == GLUT_UP ) )
        drag_mouse_r = 0;

    // 中??ンが押されたらドラッグ開始
    if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_DOWN ) )
        drag_mouse_m = 1;
    // 中??ンが離されたらドラッグ終了
    else if ( ( button == GLUT_MIDDLE_BUTTON ) && ( state == GLUT_UP ) )
        drag_mouse_m = 0;

    // 再?画
    glutPostRedisplay();

    // 現在の?ウス座標を記?
    last_mouse_x = mx;
    last_mouse_y = my;
}


//
// ?ウスドラッグ時に呼ばれるコ?ルバック関数
//
void  motion( int mx, int my )
{
    // 右??ンのドラッグ中は視?を回?する
    if ( drag_mouse_r )
    {
        // 前回の?ウス座標と今回の?ウス座標の差に応じて視?を回?

        // ?ウスの横移動に応じてＹ軸を中心に回?
        camera_yaw -= ( mx - last_mouse_x ) * 1.0;
        if ( camera_yaw < 0.0 )
            camera_yaw += 360.0;
        else if ( camera_yaw > 360.0 )
            camera_yaw -= 360.0;

        // ?ウスの縦移動に応じてＸ軸を中心に回?
        camera_pitch -= ( my - last_mouse_y ) * 1.0;
        if ( camera_pitch < -90.0 )
            camera_pitch = -90.0;
        else if ( camera_pitch > 90.0 )
            camera_pitch = 90.0;
    }
    // 左??ンのドラッグ中は視?とカメラの距離を変更する
    if ( drag_mouse_l )
    {
        // 前回の?ウス座標と今回の?ウス座標の差に応じて視?を回?

        // ?ウスの縦移動に応じて距離を移動
        camera_distance += ( my - last_mouse_y ) * 0.2;
        if ( camera_distance < 2.0 )
            camera_distance = 2.0;
    }

    // 今回の?ウス座標を記?
    last_mouse_x = mx;
    last_mouse_y = my;

    // 再?画
    glutPostRedisplay();
}


//
//  キ???ドのキ?が押されたときに呼ばれるコ?ルバック関数
//
void  keyboard( unsigned char key, int mx, int my )
{
    // s キ?でアニメ?ションの停?・再開
    if ( key == 's' )
        on_animation = !on_animation;

    // n キ?で次のフレ??
    if ( ( key == 'n' ) && !on_animation )
    {
        animation_time += bvh->GetInterval();
        frame_no ++;
        frame_no = frame_no % bvh->GetNumFrame();
    }

    // p キ?で前のフレ??
    if ( ( key == 'p' ) && !on_animation && ( frame_no > 0 ) && bvh )
    {
        animation_time -= bvh->GetInterval();
        frame_no --;
        frame_no = frame_no % bvh->GetNumFrame();
    }

    // r キ?でアニメ?ションのリセット
    if ( key == 'r' )
    {
        animation_time = 0.0f;
        frame_no = 0;
    }

    // l キ?で再生動作の変更
    if ( key == 'l' )
    {
#ifdef  WIN32
        const int  file_name_len = 256;
        char  file_name[ file_name_len ] = "";

        // フ?イル?イアログの設定
        OPENFILENAME	open_file;
        memset( &open_file, 0, sizeof(OPENFILENAME) );
        open_file.lStructSize = sizeof(OPENFILENAME);
        open_file.hwndOwner = NULL;
        open_file.lpstrFilter = "BVH Motion Data (*.bvh)\0*.bvh\0All (*.*)\0*.*\0";
        open_file.nFilterIndex = 1;
        open_file.lpstrFile = file_name;
        open_file.nMaxFile = file_name_len;
        open_file.lpstrTitle = "Select a BVH file";
        open_file.lpstrDefExt = "bvh";
        open_file.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

        // フ?イル?イアログを?示
        BOOL  ret = GetOpenFileName( &open_file );

        // フ?イルが指定されたら新しい動作を設定
        if( ret )
        {
            // 動作デ??を読み込み
            if ( bvh )
                delete  bvh;
            bvh = new BVH( file_name );

            // 読み込みに失敗したら削除
            if ( !bvh->IsLoadSuccess() )
            {
                delete  bvh;
                bvh = NULL;
            }

            //	アニメ?ションをリセット
            animation_time = 0.0f;
            frame_no = 0;
        }
#endif
    }

    glutPostRedisplay();
}


//
//  アイドル時に呼ばれるコ?ルバック関数
//
void  idle( void )
{
    // アニメ?ション処理
    if ( on_animation )
    {
#ifdef  WIN32
        // システ?時間を取得し、前回からの経過時間に応じてΔｔを決定
        static DWORD  last_time = 0;
        DWORD  curr_time = timeGetTime();
        float  delta = ( curr_time - last_time ) * 0.001f;
        if ( delta > 0.03f )
            delta = 0.03f;
        last_time = curr_time;
        animation_time += delta;
#else
        // 固定のΔｔを使用
        animation_time += 0.03f;
#endif
        // 現在のフレ??番号を計算
        if ( bvh )
        {
            frame_no = animation_time / bvh->GetInterval();
            frame_no = frame_no % bvh->GetNumFrame();
        }
        else
            frame_no = 0;

        // 再?画の指示を出す（この後で再?画のコ?ルバック関数が呼ばれる）
        glutPostRedisplay();
    }
}


//
//  環境初期化関数
//
void  initEnvironment( void )
{
    // 光源を作成する
    float  light0_position[] = { 10.0, 10.0, 10.0, 1.0 };
    float  light0_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    float  light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float  light0_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glLightfv( GL_LIGHT0, GL_POSITION, light0_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light0_diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, light0_specular );
    glLightfv( GL_LIGHT0, GL_AMBIENT, light0_ambient );
    glEnable( GL_LIGHT0 );

    // 光源計算を有効にする
    glEnable( GL_LIGHTING );

    // 物体の色情報を有効にする
    glEnable( GL_COLOR_MATERIAL );

    // Ｚテストを有効にする
    glEnable( GL_DEPTH_TEST );

    // 背面除去を有効にする
    glCullFace( GL_BACK );
    glEnable( GL_CULL_FACE );

    // 背景色を設定
    glClearColor( 0.5, 0.5, 0.8, 0.0 );

    // 初期のBVH動作デ??を読み込み
//	bvh = new BVH( "B02.bvh" );
}


//
//  メイン関数（プログラ?はここから開始）
//
int  main( int argc, char ** argv )
{
#ifdef  WIN32
    // Visual Studio 2007 のバグで、?ル?バイト文字で?されたパスに日?語を含むときに、
    // フ?イルを正しく開けないため、問題を回避するために、正しいロケ?ルを設定
    locale::global( locale("japanese") );
#endif

    // GLUTの初期化
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL );
    glutInitWindowSize( 640, 640 );
    glutInitWindowPosition( 0, 0 );
    glutCreateWindow("BVH Player Sample");
    
    // コ?ルバック関数の登?
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMouseFunc( mouse );
    glutMotionFunc( motion );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );

    // 環境初期化
    initEnvironment();

    // GLUTのメインル?プに処理を移す
    glutMainLoop();
    return 0;
}

