#!/usr/bin/env python3
import argparse
import datetime
import os
import subprocess

if __name__ == '__main__':
    os.system('git fetch')
    os.system('git checkout master')

    latest_tag = subprocess.check_output('git describe --tags $(git rev-list --tags --max-count=1)', shell=True).decode('utf-8').strip()
    latest_version, latest_date, latest_patch = latest_tag.split('-')
    latest_version = latest_version[1:]

    parser = argparse.ArgumentParser(description='Make tags for Screenshotgun')

    parser.add_argument(
        '-v',
        '--version',
        default=latest_version,
        help='Screenshotgun version',
    )

    version = parser.parse_args().version
    date = datetime.date.today().strftime('%Y%m%d')

    if latest_version == version and latest_date == date:
        tag = 'v%s-%s-%d' % (version, date, int(latest_patch) + 1)
    else:
        tag = 'v%s-%s-%d' % (version, date, 1)

    answer = input("Create tag %s? Type yes: " % tag)
    if answer == 'yes':
        os.system('git tag -a %s -m "Version: %s"' % (tag, tag))
        os.system('git push origin %s' % tag)
