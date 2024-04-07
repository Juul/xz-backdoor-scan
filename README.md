Scan for files containing the signature from the `xz` backdoor (CVE-2024-3094).

Rapidly scans files and reports back with any files found to contain the signature used in the backdoor.

WARNING: Do not trust this program to be correct or alert you about the presence of a backdoor. This is a proof of concept only. Do not rely on it for any security.

This program was not written by [juul](http://github.com/juul). It was written by `stderr`. See authorship section at the bottom.

# Usage

```
Usage:
	./xz-backdoor-scan [options] <filenames> [...]

Where [options] are:

	-h / --help
		This text

	-f / --file <filename>
		Search for content of "filename" instead of the xz-backdoor signature
	-n / --needle <needle>
		Search for "needle" instead of the xz-backdoor signature
		This is mostly useful for searching for text strings.
		For binary data, see -f / --file
```

To scan files in a directory non-recursively:

```
~# ./xz-backdoor-scan *
```

Note that the above assumes that there are _only_ files in the currenty directory.

If files containing the signature are found, the output will look something like this:

```
BAD_liblzma.so.5.6.0_from_liblzma5-udeb_5.6.0-0.1_amd64.udeb: CONTAINS THE SIGNATURE
BAD_liblzma.so.5.6.0_from_liblzma5-udeb_5.6.0-0.2_amd64.udeb: CONTAINS THE SIGNATURE
```

To rapidly scan your entire local filesystem recursively:

```
find $(df -P | awk '/^\/dev\// { print $6 }') -mount -type f -exec ./xz-backdoor-scan {} + 
```

# Signature

The signature being searched for is in `signature.c`.

# Copyright and license

Copyright 2024 stderr

License: AGPLv3

# Authorship

This program was written by `stderr` who can be found here:

* [Twitch](https://twitch.tv/stderr_dk)
* [Twitter](https://twitter.com/stderrdk)
* [Bluesky](https://bsky.app/profile/stderr.bsky.social)
* [Mastodon](https://mastodon.social/@stderr)
* [Discord](https://discord.com/invite/6tTFY6KfB8)
