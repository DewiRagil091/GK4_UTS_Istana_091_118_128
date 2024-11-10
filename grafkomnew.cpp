#include <glut.h>
#include <cmath>

// Fungsi untuk menggambar lingkaran
void drawCircle(float x, float y, float radius, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Titik tengah lingkaran
    for (int i = 0; i <= segments; i++) {
        float angle = (i * 2.0f * 3.1415926f) / segments;
        float dx = radius * cos(angle);
        float dy = radius * sin(angle);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}

// Fungsi untuk menggambar pohon
void drawTree(float x, float y) {
    // Menggambar batang pohon (persegi panjang coklat)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.25f, 0.0f);
    glVertex2f(x - 0.02f, y); 
    glVertex2f(x + 0.02f, y);
    glVertex2f(x + 0.02f, y - 0.1f);
    glVertex2f(x - 0.02f, y - 0.1f); 
    glEnd();

    // Menggambar bagian pohon (segitiga hijau)
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.7f, 0.0f);
    glVertex2f(x - 0.1f, y + 0.1f); 
    glVertex2f(x + 0.1f, y + 0.1f); 
    glVertex2f(x, y + 0.3f);

    glVertex2f(x - 0.15f, y + 0.05f); 
    glVertex2f(x + 0.15f, y + 0.05f); 
    glVertex2f(x, y + 0.2f);
    glVertex2f(x - 0.2f, y); 
    glVertex2f(x + 0.2f, y);
    glVertex2f(x, y + 0.1f); 
    glEnd();
}

// Fungsi untuk menggambar awan
void drawCloud(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); 
    drawCircle(x, y, 0.08f, 50); 
    drawCircle(x + 0.1f, y, 0.1f, 50); 
    drawCircle(x + 0.2f, y, 0.08f, 50); 
}

// Fungsi untuk menggambar matahari dengan sinar
void drawSun(float x, float y, float radius) {
    glColor3f(1.0f, 0.9f, 0.0f); 
    drawCircle(x, y, radius, 50); 

    // Menggambar sinar matahari
    glColor3f(1.0f, 0.9f, 0.0f); 
    for (int i = 0; i < 8; i++) {
        float angle = i * 45.0f * 3.1415926f / 180.0f; 
        float dx = radius * 1.5f * cosf(angle); 
        float dy = radius * 1.5f * sinf(angle); 

        glBegin(GL_LINES);
        glVertex2f(x, y);            
        glVertex2f(x + dx, y + dy);     
        glEnd();
    }
}

// Fungsi untuk menggambar istana atau bangunan kerajaan
void drawCastle(float x, float y) {
    // Gambar bangunan istana (persegi panjang besar)
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.5f, 0.9f); 
    glVertex2f(x - 0.3f, y);      
    glVertex2f(x + 0.3f, y);      
    glVertex2f(x + 0.3f, y + 0.4f); 
    glVertex2f(x - 0.3f, y + 0.4f); 
    glEnd();

    // Gambar menara istana (persegi panjang tinggi)
    glBegin(GL_QUADS);
    glColor3f(0.9f, 0.0f, 0.5f); 
    glVertex2f(x - 0.1f, y + 0.4f); 
    glVertex2f(x + 0.1f, y + 0.4f); 
    glVertex2f(x + 0.1f, y + 0.7f); 
    glVertex2f(x - 0.1f, y + 0.7f); 
    glEnd();

    // Gambar atap menara (piramida)
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.4f, 1.0f);
    glVertex2f(x - 0.15f, y + 0.7f); 
    glVertex2f(x + 0.15f, y + 0.7f); 
    glVertex2f(x, y + 0.9f);        
    glEnd();

    // Tambahkan elemen hiasan seperti jendela atau gerbang
    // Gambar jendela
    glBegin(GL_QUADS);
    glColor3f(0.6f, 0.8f, 1.0f); 
    glVertex2f(x - 0.1f, y + 0.2f);
    glVertex2f(x + 0.1f, y + 0.2f);
    glVertex2f(x + 0.1f, y + 0.3f);
    glVertex2f(x - 0.1f, y + 0.3f);
    glEnd();

    // Gambar gerbang istana (pagar kerajaan)
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.6f, 0.9f); 
    glVertex2f(x - 0.35f, y - 0.2f);
    glVertex2f(x + 0.35f, y - 0.2f); 
    glVertex2f(x + 0.35f, y);       
    glVertex2f(x - 0.35f, y);        
    glEnd();

    // Gambar tiang pagar kiri
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.8f); 
    glVertex2f(x - 0.4f, y - 0.2f); 
    glVertex2f(x - 0.3f, y - 0.2f); 
    glVertex2f(x - 0.3f, y + 0.3f); 
    glVertex2f(x - 0.4f, y + 0.3f); 
    glEnd();

    // Gambar tiang pagar kanan
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.8f); 
    glVertex2f(x + 0.4f, y - 0.2f); 
    glVertex2f(x + 0.3f, y - 0.2f); 
    glVertex2f(x + 0.3f, y + 0.3f); 
    glVertex2f(x + 0.4f, y + 0.3f); 
    glEnd();
}


void drawFinishLine() {
    // Garis vertikal kiri
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f); 
    glVertex2f(-0.95f, -0.4f);
    glVertex2f(-0.95f, -1.0f);
    glEnd();

    // Garis vertikal kanan
    glBegin(GL_LINES);
    glVertex2f(0.95f, -0.4f); 
    glVertex2f(0.95f, -1.0f); 
    glEnd();
}

//menggammbar batu rintangan
void drawBrickWall(float x, float y, int rows, int columns, float brickWidth, float brickHeight) {
    glColor3f(0.5f, 0.4f, 0.2f);

    for (int i = 0; i < rows; i++) {
        float offsetX = (i % 2 == 0) ? 0.0f : brickWidth / 2.0f; // Offset untuk pola selang-seling
        for (int j = 0; j < columns; j++) {
            float brickX = x + offsetX + j * brickWidth - (columns * brickWidth) / 2.0f;
            float brickY = y - i * brickHeight;
            glBegin(GL_QUADS);
            glVertex2f(brickX, brickY);
            glVertex2f(brickX + brickWidth, brickY);
            glVertex2f(brickX + brickWidth, brickY - brickHeight);
            glVertex2f(brickX, brickY - brickHeight);
            glEnd();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Membersihkan layar dengan warna latar belakang

    // gradasi langit 
    glBegin(GL_QUADS);
    glColor3f(0.529f, 0.808f, 0.922f);
    glVertex2f(-1.0f, 1.0f); 
    glVertex2f(1.0f, 1.0f);  
    glColor3f(1.0f, 1.0f, 1.0f); 
    glVertex2f(1.0f, 0.0f);   
    glVertex2f(-1.0f, 0.0f); 
    glEnd();

    // Menggambar tanah (rumput hijau)
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.3f, 0.0f); 
    glVertex2f(-1.0f, -1.0f); 
    glVertex2f(1.0f, -1.0f);  
    glVertex2f(1.0f, -0.4f);  
    glVertex2f(-1.0f, -0.4f); 
    glEnd();

    // Menggambar garis finish
    drawFinishLine();

    // Menggambar istana atau bangunan kerajaan
    drawCastle(0.6f, -0.3f); 

    // Menambahkan 3 pohon  kecil yang berjejer dari kiri ke kanan
    drawTree(-0.8f, -0.3f); 
    drawTree(-0.4f, -0.3f);  
    drawTree(0.0f, -0.3f);  

    // Menambahkan tiga awan cantik di langit
    drawCloud(-0.6f, 0.6f);
    drawCloud(0.0f, 0.8f); 
    drawCloud(0.6f, 0.7f);  

    // Menambahkan matahari dengan sinar
    drawSun(-0.8f, 0.8f, 0.1f); 


    // Menggambar batu bata kecil yang tersusun ke atas di posisi awal
    drawBrickWall(-0.6f, -0.7f, 6, 3, 0.05f, 0.02f);

    // Menambahkan tumpukan batu baru di samping kanan dengan jarak 0.5 unit
    drawBrickWall(-0.1f, -0.7f, 6, 3, 0.05f, 0.02f); // Tumpukan pertama di kanan
    drawBrickWall(0.4f, -0.7f, 6, 3, 0.05f, 0.02f); // Tumpukan kedua di kanan



    glutSwapBuffers(); // Menukar buffer agar tampilan diperbarui
}

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Warna latar belakang putih

    // Mengatur mode proyeksi dan mengatur sistem koordinat 2D
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Sistem koordinat 2D dengan ukuran -1.0 hingga 1.0
}

int main(int argc, char** argv) {
    // Inisialisasi GLUT dan pengaturan jendela
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Kerajaan dan Pemandangan Alam");

    init(); 

    glutDisplayFunc(display);
    glutMainLoop(); 

    return 0;
}