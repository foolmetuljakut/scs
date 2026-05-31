Name:           strategic_combat_simulation
Version:        %{getenv:APP_VERSION}
Release:        1%{?dist}
Summary:        Strategic Combat Simulation

# Debug-Pakete deaktivieren (kein Quellcode im RPM-Build vorhanden)
%global debug_package %{nil}

License:        MIT
URL:            https://github.com/yourusername/scs

# Keine Quelldateien nötig – wir liefern ein vorgebautes Binary aus
# Source0 wird nicht benötigt

Requires:       libconfig
Requires:       fmt
Requires:       spdlog

%description
A strategic combat simulation application

# Kein Entpacken von Quellen nötig
%prep
%{nil}

# Kein Compilieren – Binary ist bereits vorgebaut
%build
%{nil}

%install
# Vorgebautes Binary installieren; %{_sourcedir} zeigt auf das Projektverzeichnis
mkdir -p %{buildroot}%{_bindir}
install -m 0755 %{_sourcedir}/build/%{name} %{buildroot}%{_bindir}/%{name}

# Konfigurationsdateien installieren
mkdir -p %{buildroot}%{_sysconfdir}/%{name}

%files
%{_bindir}/strategic_combat_simulation

%changelog
* Sat Apr 19 2026 Developer <dev@example.com> - 2025.1.0-1
- Initial release
