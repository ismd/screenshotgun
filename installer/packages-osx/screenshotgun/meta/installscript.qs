function Component() {
    installer.installationFinished.connect(this, Component.prototype.installationFinishedPageIsShown);
    installer.finishButtonClicked.connect(this, Component.prototype.installationFinished);
}

Component.prototype.createOperations = function() {
    component.createOperations();
}

Component.prototype.installationFinishedPageIsShown = function() {
    if (installer.isUpdater()) {
        installer.execute("mv", [installer.value("TargetDir") + "/screenshotgun.app/Contents", installer.value("TargetDir") + "/Contents"]);

        installer.execute("rm", ["-rf", installer.value("TargetDir") + "/screenshotgun.app"]);
    }
}

Component.prototype.installationFinished = function() {
    if (installer.isUpdater()) {
        installer.executeDetached(installer.value("TargetDir") + "/Contents/MacOS/screenshotgun");
    }
}
