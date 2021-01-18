#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>

void pkgman();

int main() {
	// init variables and other useful things
	char user[32], host[253];
	struct utsname sys;

	// get user and host names
	snprintf(user, 32, "%s", getenv("USER"));
	gethostname(host, 253);

	if (uname(&sys) == -1) {
		printf("Ah sh-t, an error\n");
	}
	char version_name[64];
	FILE *fosr  = fopen("/etc/os-release", "r");
	fscanf(fosr,"%[^\n]", version_name);
	fclose(fosr);
	memmove(&version_name[0], &version_name[5], 64);
	printf("%s@%s %s %s\n", user, host, version_name, sys.machine); //debug
    pkgman();
	return 0;
}

void pkgman() {
	int apt, dnf, emerge, flatpak, nix, pacman, rpm, snap, xbps, yay;

    FILE *fapt = popen("dpkg-query -f '${binary:Package}\n' -W 2>/dev/null | wc -l", "r");
    FILE *fdnf = popen("dnf list installed 2>/dev/null | wc -l", "r");
    FILE *femerge = popen("qlist -I 2>/dev/null | wc -l", "r");
    FILE *fflatpak = popen("flatpak list 2>/dev/null | wc -l", "r");
    FILE *fnix = popen("nix-store -q --requisites /run/current-system/sw 2>/dev/null | wc -l", "r");
    FILE *fpacman = popen("pacman -Q 2>/dev/null | wc -l", "r");
    FILE *frpm = popen("rpm -qa --last 2>/dev/null | wc -l", "r");
    FILE *fsnap = popen("snap list 2>/dev/null | wc -l", "r");
    FILE *fxbps = popen("xbps-query -l 2>/dev/null | wc -l", "r");
    FILE *fyay = popen("yay -Q 2>/dev/null | wc -l", "r");
    fscanf(fapt, "%d", &apt);
    fscanf(fdnf, "%d", &dnf);
    fscanf(femerge, "%d", &emerge);
    fscanf(fflatpak, "%d", &flatpak);
    fscanf(fnix, "%d", &nix);
    fscanf(fpacman, "%d", &pacman);
    fscanf(frpm, "%d", &rpm);
    fscanf(fsnap, "%d", &snap);
    fscanf(fxbps, "%d", &xbps);
    fscanf(fyay, "%d", &yay);
    fclose(fapt);
    fclose(fdnf);
    fclose(femerge);
    fclose(fflatpak);
    fclose(fnix);
    fclose(fpacman);
    fclose(frpm);
    fclose(fsnap);
    fclose(fxbps);
    fclose(fyay);

    int comma = 0;

    if (apt > 0) {
        if (comma == 1) printf(", ");
        printf("apt: %d", apt);
        comma = 1;
    }
    if (dnf > 0) {
        if(comma == 1) printf(", ");
        printf("dnf: %d", dnf);
        comma = 1;
    }
    if (emerge > 0) {
        if (comma == 1) printf(", ");
        printf("emerge: %d", emerge);
        comma = 1;
    }
    if (flatpak > 0) {
        if (comma == 1) printf(", ");
        printf("flatpak: %d", flatpak);
        comma = 1;
    }
    if (nix > 0) {
        if (comma == 1) printf(", ");
        printf("nix: %d", nix);
        comma = 1;
    }
    if (pacman > 0) {
        if (comma == 1) printf(", ");
        printf("pacman: %d", pacman);
        comma = 1;
    }
    if (rpm > 0) {
        if (comma == 1) printf(", ");
        printf("rpm: %d", rpm);
        comma = 1;
    }
    if (snap > 0) {
        if (comma == 1) printf(", ");
        printf("snap: %d", snap);
        comma = 1;
    }
    if (xbps > 0) {
        if (comma == 1) printf(", ");
        printf("xbps: %d", xbps);
        comma = 1;
    }
    if (yay > 0) {
        if (comma == 1) printf(", ");
        printf("yay: %d", yay);
        comma = 1;
    }
    printf("\n");
}