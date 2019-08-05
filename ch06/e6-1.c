#include "apue.h"
#include <pwd.h>
#include <shadow.h>

void test_getpwent() {
	printf("begin test_getpwent()!\n");
	struct passwd *ptr;
	setpwent();
	while ((ptr = getpwent()) != NULL) {
		printf("name=%s, encrypted password=%s\n", ptr->pw_name, ptr->pw_passwd);
	}
	endpwent();
}

void test_getspent() {
	printf("begin test_getspent()!\n");
	struct spwd *ptr;
	setspent();
	while ((ptr = getspent()) != NULL) {
		printf("name=%s, shadow password=%s\n", ptr->sp_namp, ptr->sp_pwdp);
	}
	endspent();
}

int main() {
	/* getpwent() just read files that will output all encrypted password=x. */
	test_getpwent();
	/* Use sudo to run this binary will show shadow encrypted password. */
	test_getspent();
	return 0;
}

/*
 * The function to access the shadow password file on Linue and Solaris are
 * discuess in Section 6.3. We can't use the value returned in the pw_passed
 * field by the function described in Section 6.2 to compare an encrypted
 * passward, since that field is not the encrypted password. Instead, we need
 * to find the user's entry in the shadow file and use its encrypted password
 * field.
 *
 * On FreeBSD and Mac OS X, the password file is shadowed automatically. In the
 * passwd structure returned by getpwnam and get pwuid on FreeBSD 8.0, the
 * pw_passwd field contains the encrypted password, but only if the caller's
 * effective user ID is 0. On Mac OS X 10.6.8, the encrypted password is not
 * accessible using these interface.
 */

