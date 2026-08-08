# 🛡️ The Complete Cybersecurity Mastery Roadmap

> **From Absolute Beginner to Professional Cybersecurity Engineer**
> Created by a Senior Cybersecurity Mentor with 20+ years in the industry

---

## 📋 Table of Contents

1. [How to Use This Roadmap](#how-to-use-this-roadmap)
2. [Phase 0: Mindset & Setup](#phase-0-mindset--setup)
3. [Phase 1: Computer & OS Fundamentals](#phase-1-computer--os-fundamentals)
4. [Phase 2: Linux Deep Dive](#phase-2-linux-deep-dive)
5. [Phase 3: Networking Fundamentals](#phase-3-networking-fundamentals)
6. [Phase 4: Windows Internals & Active Directory](#phase-4-windows-internals--active-directory)
7. [Phase 5: Programming for Cybersecurity](#phase-5-programming-for-cybersecurity)
8. [Phase 6: Cybersecurity Fundamentals](#phase-6-cybersecurity-fundamentals)
9. [Phase 7: Cryptography](#phase-7-cryptography)
10. [Phase 8: Web Security & OWASP](#phase-8-web-security--owasp)
11. [Phase 9: Ethical Hacking & Penetration Testing](#phase-9-ethical-hacking--penetration-testing)
12. [Phase 10: Digital Forensics & Incident Response](#phase-10-digital-forensics--incident-response)
13. [Phase 11: Malware Analysis & Reverse Engineering](#phase-11-malware-analysis--reverse-engineering)
14. [Phase 12: Cloud Security](#phase-12-cloud-security)
15. [Phase 13: Containers & DevSecOps](#phase-13-containers--devsecops)
16. [Phase 14: Security Operations (Blue Team)](#phase-14-security-operations-blue-team)
17. [Phase 15: Advanced Red Teaming](#phase-15-advanced-red-teaming)
18. [Phase 16: Bug Bounty Hunting](#phase-16-bug-bounty-hunting)
19. [Certification Roadmap](#certification-roadmap)
20. [Career Tracks](#career-tracks)
21. [12-Month Learning Plan](#12-month-learning-plan)
22. [24-Month Mastery Roadmap](#24-month-mastery-roadmap)
23. [Portfolio Checklist](#portfolio-checklist)
24. [GitHub Project Roadmap](#github-project-roadmap)
25. [Interview Preparation Roadmap](#interview-preparation-roadmap)
26. [Communities & Discord Servers](#communities--discord-servers)
27. [Common Beginner Mistakes & How to Avoid Them](#common-beginner-mistakes--how-to-avoid-them)
28. [Tips for Building a Strong Cybersecurity Portfolio](#tips-for-building-a-strong-cybersecurity-portfolio)

---

## How to Use This Roadmap

### 🎯 Your Learning Workflow (The "Understand-Do-Build" Method)

```
┌─────────────────────────────────────────────────────────┐
│  1. READ theory (documentation, articles, books)        │
│  2. WATCH demonstrations (videos, walkthroughs)         │
│  3. FOLLOW ALONG labs (guided exercises)                │
│  4. BUILD projects (apply knowledge)                    │
│  5. SOLVE challenges (CTFs, puzzles)                    │
│  6. TEACH others (blog posts, notes in Obsidian)        │
└─────────────────────────────────────────────────────────┘
```

### 📝 Note-Taking with Obsidian

For each phase, create Obsidian notes structured as:

```
📁 CyberSecurity/
  ├── 📁 01-Fundamentals/
  ├── 📁 02-Linux/
  ├── 📁 03-Networking/
  ├── 📁 04-Programming/
  ├── 📁 05-Web-Security/
  ├── 📁 06-Ethical-Hacking/
  ├── 📁 07-Forensics/
  ├── 📁 08-Malware-Analysis/
  ├── 📁 09-Cloud-Security/
  ├── 📁 10-Certifications/
  └── 📁 Projects/
```

Each note should contain:
- **Concepts**: Key terms and definitions (your own words)
- **Commands**: Useful terminal commands with examples
- **Diagrams**: Mermaid or Excalidraw for visual concepts
- **Labs**: Step-by-step walkthroughs
- **Resources**: Links to what you used
- **Reflections**: What you learned and struggled with

### ✅ Progress Tracking

Use checkboxes to track your progress:

```
- [ ] Phase 1: Computer & OS Fundamentals
  - [ ] Computer Architecture
  - [ ] Operating Systems
  - [ ] Virtualization
- [ ] Phase 2: Linux Deep Dive
  ...
```

### ⏱️ Time Estimates

| Icon | Meaning |
|------|---------|
| 🟢 | 1-2 weeks |
| 🟡 | 2-4 weeks |
| 🟠 | 1-2 months |
| 🔴 | 2-3 months |
| ⚫ | 3-6 months |

---

## Phase 0: Mindset & Setup

### 🧠 The Cybersecurity Mindset

Before you write a single command, internalize these principles:

| Principle | Explanation |
|-----------|-------------|
| **Think like an attacker** | Always ask "How could this be broken?" |
| **Be relentlessly curious** | Click everything, inspect everything |
| **Embrace the grind** | You will fail 100x before you succeed |
| **Document everything** | Your future self will thank you |
| **Stay ethical** | Permission is NOT optional. Ever. |
| **Share knowledge** | The best way to learn is to teach |
| **Build, don't just consume** | Passive learning = waste of time |

### ⚙️ Your Learning Environment Setup

#### Hardware Requirements

| Component | Minimum | Recommended |
|-----------|---------|-------------|
| RAM | 8 GB | 16+ GB |
| Storage | 256 GB SSD | 512 GB+ SSD |
| CPU | i5/Ryzen 5 | i7/Ryzen 7 |
| GPU | Not required | Nice-to-have (for password cracking) |
| Internet | 10 Mbps | 50+ Mbps |

#### Software You Need Day 1

- [ ] **VirtualBox** or **VMware Workstation Player** (free)
- [ ] **Kali Linux** VM
- [ ] **Windows 10/11** VM (evaluation copy)
- [ ] **Ubuntu** VM
- [ ] **Obsidian** (for note-taking)
- [ ] **Visual Studio Code**
- [ ] **Burp Suite Community Edition**
- [ ] **Wireshark**
- [ ] **Docker Desktop** (free tier)

#### Essential Browser Extensions

- [ ] **FoxyProxy** — proxy switcher for Burp Suite
- [ ] **Wappalyzer** — identify web technologies
- [ ] **HackBar** — security testing helper (or use the built-in dev tools)
- [ ] **uBlock Origin** — block distractions

#### Your First VMs to Set Up

```bash
# Download and set up:
1. Kali Linux (attacker machine)
2. Metasploitable 2 (vulnerable target)
3. DVWA (Damn Vulnerable Web Application) - Docker
4. Windows 10 (test target)
```

### 📚 Essential Reading Before You Start

| Resource | Link | Why |
|----------|------|-----|
| The Hacker Manifesto (The Conscience of a Hacker) | [Read it](http://phrack.org/issues/7/3.html) | Understand hacker culture |
| How to Learn Hacking (The CTF Way) | [Post](https://www.peerlyst.com/posts/the-ctf-way-a-beginners-guide-to-hacking-umair-nehri) | Mindset shift |
| Rules of Engagement for Ethical Hackers | [Read](https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-115.pdf) | Legal & ethical boundaries |

**Milestone to move on**: You have Kali Linux running, can take screenshots, and have Obsidian set up with your first notes.

---

## Phase 1: Computer & OS Fundamentals

### Learning Objectives

- [ ] Understand how computers work at a high level
- [ ] Explain CPU, RAM, storage, and how they interact
- [ ] Install and navigate an operating system
- [ ] Understand processes, memory, and filesystems
- [ ] Set up and use virtual machines

### Core Concepts

- **Computer Architecture**: CPU, RAM, Motherboard, Buses, I/O
- **Binary & Hexadecimal**: Bits, bytes, why hex matters
- **Operating Systems**: What they do, kernel vs user space
- **Processes**: What they are, how they're managed
- **Memory**: Stack, heap, virtual memory, paging
- **Filesystems**: NTFS, ext4, FAT32, inodes, permissions
- **Virtualization**: Hypervisors, VMs vs containers

### Prerequisites

None — this is where you start.

### Practical Skills

- [ ] Convert between binary, decimal, and hexadecimal
- [ ] Install an OS (Ubuntu, Windows)
- [ ] Create and manage virtual machines
- [ ] Use basic file operations
- [ ] Identify system resources (CPU, RAM, disk usage)
- [ ] Understand file extensions and their meanings

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Harvard CS50 | [cs50.harvard.edu](https://cs50.harvard.edu) | Computer science fundamentals | Best intro course ever made. Free, comprehensive. | 🟢 Beginner |
| Crash Course Computer Science | [YouTube Playlist](https://www.youtube.com/playlist?list=PL8dPuuaLjXtNlUrzyH5r6jN9ulIgZBpdo) | Full CS fundamentals | Visual, engaging, 40 episodes | 🟢 Beginner |
| MIT OpenCourseWare — Computer Architecture | [OCW](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-004-computation-structures-spring-2017/) | CPU, memory, architecture | MIT-level depth, free | 🟡 Intermediate |
| freeCodeCamp — Computer Science | [YouTube](https://www.youtube.com/watch?v=8pt0Y5MpLvs) | Full computer science crash course | 2-hour concise overview | 🟢 Beginner |
| Professor Messer — CompTIA A+ (220-1001) | [YouTube](https://www.youtube.com/playlist?list=PLG49S3nxzAnlCJi2gHvCjU0JgC2Dpv0p5) | Hardware & OS fundamentals | Industry standard, great instructor | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Build a computer (virtual) | Configure a VM with specific RAM, CPU, storage | Hardware fundamentals |
| Binary calculator | Write a script that converts binary ↔ decimal ↔ hex | Number systems |
| OS comparison chart | Document differences between Windows, Linux, macOS | OS knowledge |
| Boot process diagram | Trace what happens from power-on to login screen | Architecture knowledge |

### Labs & Exercises

- **Lab 1**: Create 3 VMs (Kali, Ubuntu, Windows 10) and network them
- **Lab 2**: Use Task Manager (Windows) and `top` (Linux) to examine processes
- **Lab 3**: Explore the filesystem tree on both Windows and Linux
- **Lab 4**: Check memory usage, disk space, and CPU with system tools

### ⏱️ Estimated Time: 2-4 weeks 🟡

### 🏁 Milestone Before Moving On

- [ ] I can explain what happens when I press the power button
- [ ] I can convert between binary, decimal, and hex fluently
- [ ] I have 3 working VMs and can SSH between them
- [ ] I understand the difference between process, thread, and program
- [ ] I have Obsidian notes for all concepts in this phase

---

## Phase 2: Linux Deep Dive

### Learning Objectives

- [ ] Master the Linux command line
- [ ] Understand Linux filesystem hierarchy
- [ ] Manage users, groups, and permissions
- [ ] Configure networking from the terminal
- [ ] Write Bash scripts
- [ ] Manage services and processes
- [ ] Understand Linux security features

### Core Concepts

- **File System Hierarchy (FHS)**: `/bin`, `/etc`, `/var`, `/tmp`, `/home`, `/root`
- **File Permissions**: rwx, chmod, chown, chgrp, SUID, SGID, Sticky Bit
- **Users & Groups**: /etc/passwd, /etc/shadow, /etc/group
- **Process Management**: ps, top, htop, kill, nice, systemd
- **Service Management**: systemctl, service, journalctl
- **Networking**: ip, nmcli, ss, netstat, iptables, nftables
- **Package Management**: apt, dpkg, snap, flatpak
- **Logging**: rsyslog, journald, /var/log
- **SSH**: keys, config, tunnels, agents
- **Cron & Scheduling**: crontab, systemd timers
- **Shell Scripting**: variables, loops, conditionals, functions

### Prerequisites

- [x] Phase 1 completed

### Practical Skills

- [x] Navigate the filesystem without a mouse
- [ ] Manage file permissions (chmod 777, 644, 755)
- [ ] Create and manage users and groups
- [ ] Set up SSH keys and disable password auth
- [ ] Write 10+ Bash automation scripts
- [ ] Configure a firewall with iptables/ufw
- [ ] Schedule tasks with cron
- [ ] Analyze system logs for security events
- [ ] Use grep, awk, sed, find like a pro

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Linux Journey | [linuxjourney.com](https://linuxjourney.com) | Complete Linux fundamentals | Gamified, structured, perfect for beginners | 🟢 Beginner |
| freeCodeCamp — Linux for Hackers | [YouTube](https://www.youtube.com/watch?v=3G6kzHnJw2M) | Linux basics + hacking tools | Practical, hands-on | 🟢 Beginner |
| OverTheWire: Bandit | [overthewire.org](https://overthewire.org/wargames/bandit/) | Linux command line wargame | Best way to learn Linux commands by doing | 🟢 Beginner |
| Linux Command Line (Todd McLeod) | [YouTube](https://www.youtube.com/playlist?list=PLJbPQEas-DMhIwV_yLzZFOdIH5mtz7qH6) | Comprehensive CLI mastery | In-depth, well-explained | 🟢 Beginner |
| Cisco NDG Linux Unhatched | [skillsforall.com](https://skillsforall.com/course/ndg-linux-unhatched) | Linux basics | Free, structured, certification-aligned | 🟢 Beginner |
| Bash Guide for Beginners | [tldp.org](https://tldp.org/LDP/Bash-Beginners-Guide/html/) | Bash scripting reference | Comprehensive reference | 🟡 Intermediate |
| The Linux Documentation Project | [tldp.org](https://tldp.org/) | Every Linux topic | The original, authoritative source | 🟡 Intermediate |
| picoCTF | [picoctf.com](https://picoctf.com) | CTF challenges including Linux | The best beginner CTF platform, ever-growing challenges | 🟢 Beginner |
| **roadmap.sh** — Linux | [roadmap.sh/linux](https://roadmap.sh/linux) | Visual Linux roadmap | Community-driven, always up-to-date | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Auto User Manager | Script that creates/deletes users from a CSV | User mgmt, scripting |
| Log Analyzer | Script that parses /var/log/auth.log for failed SSH attempts | Log analysis, regex |
| System Monitor Dashboard | Bash script that outputs CPU/RAM/disk in a nice table | Process mgmt, scripting |
| Hardening Script | Script that configures firewall, disables root SSH, sets password policies | Security hardening |
| Custom Cron Backups | Automated backup script with rotation | Cron, archiving |

### Labs & Exercises

- **Lab 1**: Complete Bandit levels 0-34 on OverTheWire
- **Lab 2**: Set up a LAMP stack (Linux, Apache, MySQL, PHP) from scratch
- **Lab 3**: Configure SSH key-based auth + disable password login
- **Lab 4**: Build a firewall with iptables that only allows SSH, HTTP, HTTPS
- **Lab 5**: Find all SUID binaries on the system and analyze what they do
- **Lab 6**: Set up a syslog server that receives logs from another machine

### ⏱️ Estimated Time: 4-8 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I can complete OverTheWire Bandit levels 0-34 without help
- [ ] I can write a Bash script with variables, loops, and functions
- [ ] I understand Linux file permissions including SUID/SGID
- [ ] I can configure SSH, cron, and systemd services
- [ ] I have hardened a Linux server following security best practices

---

## Phase 3: Networking Fundamentals

### Learning Objectives

- [ ] Understand how data travels across networks
- [ ] Master the OSI and TCP/IP models
- [ ] Configure IP addresses, subnets, and routing
- [ ] Understand key protocols (HTTP, DNS, DHCP, SSH, etc.)
- [ ] Analyze network traffic with Wireshark
- [ ] Configure firewalls and understand NAT
- [ ] Troubleshoot network issues

### Core Concepts

**OSI Model (7 Layers)**:
```
7. Application   → HTTP, FTP, DNS, SMTP
6. Presentation  → TLS/SSL, Encryption, Compression
5. Session       → NetBIOS, RPC, Session management
4. Transport     → TCP, UDP, Ports
3. Network       → IP, ICMP, ARP, Routing
2. Data Link     → MAC, Ethernet, Switching, VLANs
1. Physical      → Cables, Hubs, Signals
```

**TCP/IP Model (4 Layers)**:
```
4. Application   → HTTP, DNS, SMTP, FTP, SSH
3. Transport     → TCP, UDP
2. Internet      → IP, ICMP, ARP
1. Network       → Ethernet, Frame Relay
```

**Key Protocols**:

| Protocol | Port | Purpose |
|----------|------|---------|
| HTTP | 80 | Web traffic |
| HTTPS | 443 | Encrypted web traffic |
| DNS | 53 | Name resolution |
| DHCP | 67/68 | IP address assignment |
| SSH | 22 | Secure remote access |
| FTP | 21 | File transfer |
| SMTP | 25 | Email sending |
| POP3 | 110 | Email receiving |
| IMAP | 143 | Email receiving (with folders) |
| SMB | 445 | Windows file sharing |
| RDP | 3389 | Remote Desktop |

### Prerequisites

- [x] Phases 1 & 2 completed

### Practical Skills

- [ ] Subnet IPv4 addresses manually and with CIDR notation
- [ ] Use Wireshark to capture and analyze traffic
- [ ] Configure a small network with static IPs
- [ ] Set up a DNS server
- [ ] Configure a firewall (iptables, pfSense)
- [ ] Capture and analyze a TCP three-way handshake
- [ ] Troubleshoot connectivity issues (ping, traceroute, nslookup)
- [ ] Read and interpret packet captures

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Cisco Skills for All — Networking Basics | [skillsforall.com](https://skillsforall.com/course/networking-basics) | Complete networking fundamentals | Created by Cisco, industry gold standard | 🟢 Beginner |
| Professor Messer — Network+ (N10-008) | [YouTube Playlist](https://www.youtube.com/playlist?list=PLG49S3nxzAnmlC8mPcmlE4B7T4VKexZ4u) | Full Networking course | Best free networking lectures | 🟡 Intermediate |
| freeCodeCamp — Computer Networking Course | [YouTube](https://www.youtube.com/watch?v=qiQR5rTSshw) | Network concepts from scratch | 1.5 hours, well-paced | 🟢 Beginner |
| Practical Networking (YouTube) | [YouTube Channel](https://www.youtube.com/c/PracticalNetworking) | Subnetting, TCP/IP, protocols | Amazing visual explanations | 🟢 Beginner |
| Wireshark Tutorial (Chris Greer) | [YouTube Playlist](https://www.youtube.com/playlist?list=PLW8bTPfXNGdC5Co7V0m8PuaQpA2zkSq26) | Wireshark mastery | Best Wireshark tutorials | 🟡 Intermediate |
| Subnetting Practice | [subnettingpractice.com](https://subnettingpractice.com) | Subnet exercises | Practice until it's automatic | 🟢 Beginner |
| Cisco Packet Tracer | [skillsforall.com](https://skillsforall.com/course/getting-started-cisco-packet-tracer) | Network simulation | Build virtual networks | 🟢 Beginner |
| TryHackMe — Network Fundamentals | [tryhackme.com](https://tryhackme.com/module/network-fundamentals) | Interactive networking labs | Hands-on with browser-based labs | 🟢 Beginner |
| **edX** — Computer Networking (audit free) | [edx.org](https://www.edx.org/learn/computer-networking) | University-level networking | Audit top university courses for free | 🟡 Intermediate |
| **OpenLearn** — IT & Networking | [open.edu/openlearn/](https://www.open.edu/openlearn/science-maths-technology/computing-ict) | Networking fundamentals | Free, accredited, well-structured | 🟢 Beginner |
| **roadmap.sh** — Networking | [roadmap.sh](https://roadmap.sh/cyber-security) | Visual networking roadmap | Community-vetted learning paths, always updating | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Build a Home Network Lab | Router, switch, 2 PCs, server (all virtual) | VLANs, routing, DHCP |
| Wireshark Capture Analysis | Capture traffic and identify all protocols | Packet analysis |
| DNS Server Setup | Set up BIND or dnsmasq | DNS, configuration |
| Network Scanner | Build a Python script that scans local network | nmap-like tool building |
| pfSense Firewall | Set up pfSense VM with rules, NAT, VPN | Firewall, routing, NAT |
| HTTP Packet Dissector | Analyze HTTP requests/responses in Wireshark | HTTP, protocol analysis |

### Labs & Exercises

- **Lab 1**: Capture a TCP three-way handshake in Wireshark
- **Lab 2**: Use Cisco Packet Tracer to build a network with 3 VLANs and inter-VLAN routing
- **Lab 3**: Configure DHCP and DNS servers on Linux
- **Lab 4**: Set up an OpenVPN server and client
- **Lab 5**: Use nmap to scan a target and identify all open ports and services
- **Lab 6**: Analyze a PCAP file and identify 5 different protocols
- **Lab 7**: Implement NAT/PAT on a router

### ⏱️ Estimated Time: 4-8 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I can subnet any IP address in my head
- [ ] I have captured and analyzed network traffic in Wireshark
- [ ] I understand how TCP, UDP, DNS, DHCP, and HTTP work
- [ ] I can configure a network with multiple VLANs
- [ ] I can use nmap effectively for network discovery

---

## Phase 4: Windows Internals & Active Directory

### Learning Objectives

- [ ] Understand Windows OS architecture
- [ ] Master Windows command line and PowerShell
- [ ] Understand Active Directory components and attacks
- [ ] Configure Group Policy
- [ ] Analyze Windows security events
- [ ] Understand Windows authentication (NTLM, Kerberos)
- [ ] Work with the Windows Registry

### Core Concepts

**Windows Architecture**:
- Kernel vs User Mode
- Win32 API
- Processes, Threads, Handles
- Windows Subsystem for Linux (WSL)

**Active Directory**:
- Domain Controllers
- Organizational Units (OUs)
- Domain, Tree, Forest
- Users, Groups, Computers
- Group Policy Objects (GPOs)
- LDAP

**Windows Security**:
- **NTLM Authentication** — Challenge-response, LM/NT hashes
- **Kerberos Authentication** — Tickets, TGT, TGS
- **SAM & LSASS** — Where credentials are stored
- **Event Viewer** — Security logs (Event IDs)
- **Windows Defender** — AV, ASR rules
- **User Account Control (UAC)**
- **AppLocker**
- **BitLocker**

**PowerShell**:
- Cmdlets and modules
- Pipeline and object manipulation
- Remoting (WinRM)
- Execution policies
- Scripting for security

### Prerequisites

- [x] Phases 1-3 completed

### Practical Skills

- [ ] Navigate Windows without a mouse (PowerShell, Run commands)
- [ ] Set up an Active Directory domain (with VMs)
- [ ] Write PowerShell scripts for automation
- [ ] Analyze Windows Event Logs for security events
- [ ] Extract password hashes from a Windows machine
- [ ] Configure Group Policy for security hardening
- [ ] Use Sysinternals tools (Process Explorer, Autoruns, etc.)
- [ ] Understand Windows privilege escalation vectors

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Microsoft Learn — Windows Fundamentals | [learn.microsoft.com](https://learn.microsoft.com/en-us/training/windows/) | Windows OS fundamentals | Official Microsoft, high quality | 🟢 Beginner |
| Microsoft Learn — Active Directory | [learn.microsoft.com](https://learn.microsoft.com/en-us/training/modules/introduction-to-active-directory/) | AD concepts and setup | Official training, step-by-step | 🟡 Intermediate |
| John Savill's Technical Training (YouTube) | [YouTube Playlist](https://www.youtube.com/c/NTKNET) | Azure & Active Directory | Best AD tutorials on YouTube | 🟡 Intermediate |
| PowerShell for Beginners | [YouTube Playlist](https://www.youtube.com/playlist?list=PLhFf_pX_W_AGqJp8qns40nvgrfDB5n58C) | PowerShell from scratch | Project-focused, practical | 🟢 Beginner |
| TryHackMe — Windows Fundamentals | [tryhackme.com](https://tryhackme.com/module/windows-fundamentals) | Interactive Windows labs | Hands-on, browser-based | 🟢 Beginner |
| TryHackMe — Active Directory | [tryhackme.com](https://tryhackme.com/room/activedirectorybasics) | AD hands-on | Practical AD exploration | 🟡 Intermediate |
| Hack The Box — Academy Windows Track | [academy.hackthebox.com](https://academy.hackthebox.com) | Windows exploitation | Free modules available | 🟡 Intermediate |
| Windows Sysinternals Suite | [learn.microsoft.com](https://learn.microsoft.com/en-us/sysinternals/) | Advanced Windows tools | Must-know for any Windows security work | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Build a Home Lab Domain | Set up AD, DNS, DHCP with Windows Server + client | AD infrastructure |
| PowerShell Inventory Script | Script that inventories all machines on a domain | PowerShell remoting |
| Event Log Monitor | PowerShell script that monitors critical security events | Event Logs, detection |
| Group Policy Hardening | Create GPOs for password policy, audit policy, software restriction | GPO security |
| Windows Attack Lab | Attack and defend a Windows domain in your lab | Red/blue team skills |

### Labs & Exercises

- **Lab 1**: Install Windows Server and promote to Domain Controller
- **Lab 2**: Join Windows 10/11 client to the domain
- **Lab 3**: Create OUs, users, groups, and delegate permissions
- **Lab 4**: Configure password policy and audit policy via GPO
- **Lab 5**: Use Sysinternals Process Monitor to analyze running processes
- **Lab 6**: Analyze Windows Event ID 4625 (failed logon), 4624 (successful logon), 4672 (admin logon)
- **Lab 7**: Extract hashes with mimikatz (in your own lab only!)
- **Lab 8**: Perform a basic Kerberos attack (AS-REP roasting, Kerberoasting)

### ⏱️ Estimated Time: 4-6 weeks 🟡

### 🏁 Milestone Before Moving On

- [ ] I can set up an Active Directory domain from scratch
- [ ] I can write PowerShell scripts with variables, loops, and functions
- [ ] I understand NTLM vs Kerberos authentication
- [ ] I can analyze Windows Event Logs for suspicious activity
- [ ] I have used Sysinternals tools for process analysis

---

## Phase 5: Programming for Cybersecurity

### Learning Objectives

- [ ] Write Python scripts for security automation
- [ ] Use Bash for Linux automation
- [ ] Use PowerShell for Windows automation
- [ ] Understand web technologies (HTML, JS, APIs)
- [ ] Write SQL queries (with security focus)
- [ ] Master regular expressions

### Core Concepts

**Python** (Focus: Security Automation):
- Sockets, requests, Scapy
- File I/O, OS module
- Subprocesses
- Cryptography libraries
- Web scraping
- API interaction
- Pcap processing
- Brute force tools

**Bash** (Focus: Linux Automation):
- String manipulation
- File processing
- Network tools
- Log parsing
- Automation scripts

**PowerShell** (Focus: Windows Automation):
- Cmdlets for security
- Active Directory module
- File system manipulation
- Event log queries
- Remote management

**JavaScript** (Focus: Web Security):
- DOM manipulation
- Fetch API
- Authentication flows
- Understanding XSS and CSRF
- Reading browser dev tools

**SQL** (Focus: Database Security):
- SELECT, WHERE, JOIN
- UNION queries
- SQL injection vectors
- Database enumeration

**Regular Expressions**:
- Pattern matching
- Log parsing
- Input validation
- Payload crafting

### Prerequisites

- [x] Phases 1-4 completed

### Practical Skills

**Python**:
- [ ] Write a port scanner
- [ ] Write a directory brute-forcer
- [ ] Parse PCAP files with Scapy
- [ ] Build a keylogger (educational)
- [ ] Automate web requests with `requests`/`beautifulsoup`
- [ ] Create a simple hash cracker

**Bash**:
- [ ] Parse and analyze log files
- [ ] Automate system administration tasks
- [ ] Build a network scanner with Bash + netcat

**PowerShell**:
- [ ] Query Active Directory
- [ ] Analyze event logs
- [ ] Automate Windows hardening

**SQL**:
- [ ] Write complex JOIN queries
- [ ] Perform SQL injection on DVWA
- [ ] Extract data from a database

### Free Resources

#### Python

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| Python Official Tutorial | [docs.python.org/3/tutorial/](https://docs.python.org/3/tutorial/) | Python fundamentals | 🟢 Beginner |
| freeCodeCamp — Python for Everybody | [YouTube](https://www.youtube.com/watch?v=8DvywoWv6fY) | Complete Python course | 🟢 Beginner |
| Google's Python Class | [developers.google.com/edu/python](https://developers.google.com/edu/python) | Python with practical exercises | 🟢 Beginner |
| Automate the Boring Stuff (Free) | [automatetheboringstuff.com](https://automatetheboringstuff.com) | Python automation | 🟢 Beginner |
| TCM Security — Python for Hackers | [YouTube](https://www.youtube.com/watch?v=H4YRP4HrPNs) | Python for infosec specifically | 🟡 Intermediate |
| Black Hat Python (Book) | [nostarch.com](https://nostarch.com/blackhatpython) | Python for offensive security | 🟡 Intermediate |
| Practice: HackerRank Python | [hackerrank.com](https://hackerrank.com/domains/python) | Python practice challenges | 🟢 Beginner |
| Practice: LeetCode | [leetcode.com](https://leetcode.com) | Algorithmic practice | 🟡 Intermediate |
| Practice: Codewars | [codewars.com](https://codewars.com) | Python katas | 🟢 Beginner |

#### Bash

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| Bash Scripting Tutorial | [ryanstutorials.net/bash-scripting-tutorial/](https://ryanstutorials.net/bash-scripting-tutorial/) | Bash from zero | 🟢 Beginner |
| Shell Scripting (freeCodeCamp) | [YouTube](https://www.youtube.com/watch?v=v-F3YLd6oMw) | Bash scripting video | 🟢 Beginner |
| Bash Guide | [mywiki.wooledge.org/BashGuide](https://mywiki.wooledge.org/BashGuide) | In-depth reference | 🟡 Intermediate |

#### PowerShell

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| Microsoft Learn — PowerShell | [learn.microsoft.com](https://learn.microsoft.com/en-us/training/modules/introduction-to-powershell/) | PowerShell basics | 🟢 Beginner |
| PowerShell for SysAdmins (YouTube) | [YouTube Playlist](https://www.youtube.com/playlist?list=PL6D2nP4vJzjb0Xy8jD5s3fWfM4Y5t5Zf9) | Practical PowerShell | 🟢 Beginner |
| PowerShell.org eBooks | [powershell.org](https://powershell.org/ebooks/) | Free PowerShell books | 🟡 Intermediate |

#### JavaScript

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| freeCodeCamp JavaScript | [freecodecamp.org](https://www.freecodecamp.org/learn/javascript-algorithms-and-data-structures/) | Complete JS course | 🟢 Beginner |
| The Modern JavaScript Tutorial | [javascript.info](https://javascript.info) | Comprehensive JS guide | 🟢 Beginner |
| MDN Web Docs | [developer.mozilla.org](https://developer.mozilla.org/en-US/docs/Web/JavaScript) | JS reference | 🟢 Beginner |

#### SQL

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| SQLbolt | [sqlbolt.com](https://sqlbolt.com) | Interactive SQL | 🟢 Beginner |
| SQLZoo | [sqlzoo.net](https://sqlzoo.net) | SQL practice | 🟢 Beginner |
| Mode Analytics SQL Tutorial | [mode.com/sql-tutorial/](https://mode.com/sql-tutorial/) | SQL fundamentals | 🟢 Beginner |
| PortSwigger SQL Injection | [portswigger.net/web-security/sql-injection](https://portswigger.net/web-security/sql-injection) | SQLi for security | 🟡 Intermediate |

#### Regular Expressions

| Resource | Link | What It Teaches | Difficulty |
|----------|------|-----------------|------------|
| RegexOne | [regexone.com](https://regexone.com) | Interactive regex | 🟢 Beginner |
| Regex Crossword | [regexcrossword.com](https://regexcrossword.com) | Regex puzzles | 🟢 Beginner |
| Regex101 | [regex101.com](https://regex101.com) | Test and debug regex | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Port Scanner (Python) | TCP connect scanner with multithreading | Sockets, threading |
| Hash Cracker (Python) | MD5/SHA256 hash cracker with dict attack | Cryptography, file I/O |
| Log Parser (Bash) | Analyze Apache logs for suspicious activity | Regex, log analysis |
| AD Reporter (PowerShell) | Script that reports all users, groups, computers in AD | AD module, PowerShell |
| Keylogger (Python) | Log keystrokes (for your own lab only!) | Input monitoring |
| SQL Injection Tool | Automated SQLi exploitation script | Python, SQL |
| Subdomain Enumerator (Python) | Brute-force subdomains with wordlist | Requests, threading |
| URL Fuzzer (Python) | Directory/file discovery tool | HTTP, automation |

### Labs & Exercises

- **Lab 1**: Build a port scanner and test against Metasploitable
- **Lab 2**: Automate DVWA SQL injection with Python requests
- **Lab 3**: Write a Bash script that monitors /var/log for failed SSH attempts and emails you
- **Lab 4**: Create a PowerShell script that extracts all domain admin group members
- **Lab 5**: Use regex to extract all IP addresses from a log file
- **Lab 6**: Build a simple reverse shell in Python

### ⏱️ Estimated Time: 6-10 weeks 🟠 (spread across other phases)

### 🏁 Milestone Before Moving On

- [ ] I can write a Python script that interacts with a network service
- [ ] I can write a Bash script that automates system administration
- [ ] I can write a PowerShell script that queries AD
- [ ] I understand SQL injection and can exploit it manually
- [ ] I can write complex regex patterns for log parsing

---

## Phase 6: Cybersecurity Fundamentals

### Learning Objectives

- [ ] Understand core security principles
- [ ] Apply risk management frameworks
- [ ] Understand authentication, authorization, accounting (AAA)
- [ ] Master the CIA triad in practice
- [ ] Understand threat modeling methodologies
- [ ] Implement security policies
- [ ] Understand Zero Trust architecture

### Core Concepts

**CIA Triad**:
- **Confidentiality** — Encryption, access control (only authorized can see)
- **Integrity** — Hashing, digital signatures (data hasn't been tampered)
- **Availability** — Redundancy, backups, DoS protection

**Security Principles**:
- Least Privilege
- Defense in Depth
- Separation of Duties
- Fail Secure
- Economy of Mechanism
- Complete Mediation
- Open Design
- Psychological Acceptability

**Risk Management**:
- Risk = Threat × Vulnerability × Impact
- NIST Risk Management Framework (RMF)
- Qualitative vs Quantitative Risk Assessment
- Risk Treatment: Accept, Mitigate, Transfer, Avoid

**Threat Modeling**:
- STRIDE (Spoofing, Tampering, Repudiation, Info Disclosure, DoS, Elevation)
- PASTA (Process for Attack Simulation and Threat Analysis)
- DREAD (Damage, Reproducibility, Exploitability, Affected Users, Discoverability)

**Authentication & Authorization**:
- Something you know (password)
- Something you have (token, phone)
- Something you are (biometrics)
- Somewhere you are (geolocation)
- MFA / 2FA
- SSO, SAML, OAuth, OpenID Connect

**Security Policies:**
- Password policies
- Acceptable Use Policy (AUP)
- Incident Response Policy
- Data Classification Policy
- Business Continuity / Disaster Recovery

**Zero Trust**:
- "Never trust, always verify"
- Micro-segmentation
- Least privilege access
- Continuous monitoring

### Prerequisites

- [x] Phases 1-5 completed

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Google Cybersecurity Certificate (audit free) | [coursera.org/professional-certificates/google-cybersecurity](https://www.coursera.org/professional-certificates/google-cybersecurity) | Comprehensive security fundamentals | Industry-led, highly respected | 🟢 Beginner |
| Professor Messer — Security+ (SY0-701) | [YouTube Playlist](https://www.youtube.com/playlist?list=PLG49S3nxzAnkX2d2Lb2SMIFxCVuTJR5Bi) | Full security fundamentals | Best free Security+ prep | 🟡 Intermediate |
| ISC2 Certified in Cybersecurity (CC) — Free | [isc2.org](https://www.isc2.org/landing/1MMCC) | Entry-level security certification | Completely free with exam | 🟢 Beginner |
| freeCodeCamp — Information Security | [YouTube](https://www.youtube.com/watch?v=hEKgI7eUuAE) | Security fundamentals | Excellent overview | 🟢 Beginner |
| MIT OpenCourseWare — Computer Systems Security | [ocw.mit.edu](https://ocw.mit.edu/courses/6-858-computer-systems-security-fall-2014/) | MIT-level security course | Deep, academic, rigorous | 🔴 Advanced |
| OWASP — Security Knowledge Framework | [owasp.org](https://owasp.org/www-project-security-knowledge-framework/) | Security by design | Industry standard for appsec | 🟡 Intermediate |
| Cybrary — Introduction to IT & Cybersecurity | [cybrary.it](https://www.cybrary.it/course/introduction-to-it-and-cybersecurity/) | Security foundations | Structured, free | 🟢 Beginner |
| NIST Cybersecurity Framework | [nist.gov/cyberframework](https://www.nist.gov/cyberframework) | Industry framework | Must-know for any security role | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Security Policy Document | Write an AUP and Incident Response policy for a fake company | Policy writing, compliance |
| Risk Assessment | Perform a risk assessment on a small business setup | Risk management |
| Threat Model | Create a threat model for a web application using STRIDE | Threat modeling |
| MFA Implementation | Set up MFA on a Linux server (Google Authenticator) | Authentication |
| Security Architecture Diagram | Draw a defense-in-depth network architecture | Architecture design |

### Labs & Exercises

- **Lab 1**: Perform a risk assessment using NIST SP 800-30
- **Lab 2**: Create a threat model for a home banking application
- **Lab 3**: Set up MFA on a Linux server
- **Lab 4**: Configure a password policy on Windows Server via GPO
- **Lab 5**: Implement file encryption (EFS on Windows, GPG on Linux)
- **Lab 6**: Create a Security Incident Response Plan

### ⏱️ Estimated Time: 4-6 weeks 🟡

### 🏁 Milestone Before Moving On

- [ ] I can explain the CIA triad with real-world examples
- [ ] I can perform a basic risk assessment
- [ ] I can threat model an application using STRIDE
- [ ] I understand the difference between authN and authZ
- [ ] I have a foundational understanding of Zero Trust

---

## Phase 7: Cryptography

### Learning Objectives

- [ ] Understand symmetric vs asymmetric encryption
- [ ] Understand hashing and its security applications
- [ ] Work with digital signatures and certificates
- [ ] Understand TLS/SSL in practice
- [ ] Use cryptography tools (OpenSSL, GPG)
- [ ] Understand PKI infrastructure
- [ ] Analyze common cryptographic attacks

### Core Concepts

**Symmetric Encryption**:
- AES (128, 256)
- DES/3DES (legacy, not secure)
- Stream vs Block Ciphers
- ECB vs CBC vs GCM modes
- IV (Initialization Vector)

**Asymmetric Encryption**:
- RSA (key generation, encryption, signatures)
- ECC (Elliptic Curve Cryptography)
- Diffie-Hellman Key Exchange
- Forward Secrecy (Ephemeral Diffie-Hellman)

**Hashing**:
- MD5, SHA-1 (broken — don't use)
- SHA-256, SHA-3 (secure)
- HMAC (Hash-based Message Authentication Code)
- Password hashing: bcrypt, scrypt, argon2
- Salting passwords

**Digital Certificates & PKI**:
- X.509 certificates
- Certificate Authorities (CAs)
- Certificate chains
- Self-signed certificates
- Certificate pinning
- Let's Encrypt (free CAs)

**TLS/SSL**:
- TLS 1.2 vs 1.3
- Certificate validation
- Cipher suites
- TLS handshake
- Perfect Forward Secrecy

**Common Attacks**:
- Frequency analysis
- Rainbow tables
- Birthday attack
- Man-in-the-Middle
- Padding oracle attack
- Downgrade attacks (e.g., POODLE)

### Prerequisites

- [x] Phases 1-6 completed (or concurrent with Phase 6)

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Cryptohack | [cryptohack.org](https://cryptohack.org) | Interactive cryptography challenges | Gamified, best for hands-on learning | 🟡 Intermediate |
| Crypto 101 (Book) | [crypto101.io](https://www.crypto101.io) | Free introductory book | Clear, accessible explanations | 🟢 Beginner |
| Computerphile — Cryptography (YouTube) | [YouTube Playlist](https://www.youtube.com/playlist?list=PLzH6n4zXuckqZ50z3Bo_X3QGBQMsWpJo2) | Visual cryptography explanations | Excellent for visual learners | 🟢 Beginner |
| Dan Boneh — Cryptography (Stanford) | [Coursera](https://www.coursera.org/learn/crypto) (audit free) | University-level cryptography | Best academic course | 🔴 Advanced |
| freeCodeCamp — Cryptography Course | [YouTube](https://www.youtube.com/watch?v=NuyzuNBFWxQ) | Full crytography course | 5+ hours of content | 🟡 Intermediate |
| OpenSSL Cookbook | [feistyduck.com/openssl-cookbook/](https://www.feistyduck.com/openssl-cookbook/) | Practical OpenSSL usage | The practical guide to TLS and crypto tools | 🟡 Intermediate |
| BetterCrypto — Applied Crypto (PDF) | [bettercrypto.org](https://bettercrypto.org) | Applied crypto best practices | Free, practical, regularly updated | 🟡 Intermediate |
| CryptoPals (Cryptopals) | [cryptopals.com](https://cryptopals.com) | Crypto challenges | Famous, excellent progression | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| File Encryptor (Python) | CLI tool that encrypts/decrypts files with AES | Symmetric encryption |
| Hash Cracker | Multi-algorithm hash cracker | Hashing, dictionary attacks |
| Certificate Analyzer | Script that parses and validates X.509 certs | PKI, OpenSSL |
| TLS Version Checker | Check what TLS versions a server supports | TLS, sockets |
| Password Manager (Basic) | Local encrypted password vault | Encryption, secure storage |

### Labs & Exercises

- **Lab 1**: Use OpenSSL to generate RSA keys, encrypt a file, and decrypt it
- **Lab 2**: Create a self-signed certificate and set up HTTPS on Apache/NGINX
- **Lab 3**: Use Wireshark to analyze a TLS handshake
- **Lab 4**: Crack MD5 hashes with Hashcat (using a wordlist + rules)
- **Lab 5**: Complete Cryptohack challenges (at least the first 20)
- **Lab 6**: Verify a digital signature using GPG
- **Lab 7**: Set up Let's Encrypt on a web server

### ⏱️ Estimated Time: 3-5 weeks 🟡

### 🏁 Milestone Before Moving On

- [ ] I understand the difference between symmetric and asymmetric encryption
- [ ] I can use OpenSSL for encryption, decryption, signing, and verification
- [ ] I understand how TLS handshake works
- [ ] I can identify common hash types
- [ ] I've completed at least 20 Cryptohack challenges

---

## Phase 8: Web Security & OWASP

### Learning Objectives

- [ ] Understand HTTP protocol deeply
- [ ] Master the OWASP Top 10 vulnerabilities
- [ ] Exploit and defend against XSS, SQLi, CSRF, SSRF
- [ ] Use Burp Suite for web application testing
- [ ] Understand API security (JWT, OAuth, CORS)
- [ ] Perform a full web application penetration test

### Core Concepts

**HTTP Deep Dive**:
- Request/Response structure
- Methods (GET, POST, PUT, DELETE, PATCH, OPTIONS)
- Headers (Host, Cookie, Authorization, Content-Type, Referer)
- Status codes (1xx, 2xx, 3xx, 4xx, 5xx)
- Sessions and cookies
- HTTPS and certificate validation

**OWASP Top 10 (2021)**:

| # | Vulnerability | What It Is |
|---|---------------|------------|
| 1 | Broken Access Control | Users access unauthorized resources |
| 2 | Cryptographic Failures | Weak encryption, exposed data |
| 3 | Injection | SQL, NoSQL, OS, LDAP injection |
| 4 | Insecure Design | Architectural flaws |
| 5 | Security Misconfiguration | Default creds, unpatched systems |
| 6 | Vulnerable Components | Outdated libraries |
| 7 | AuthN Failures | Weak login, session management |
| 8 | Data Integrity Failures | Insecure deserialization |
| 9 | Logging & Monitoring Failures | No visibility into attacks |
| 10 | SSRF | Server-side request forgery |

**Key Web Attacks**:

| Attack | Description | Impact |
|--------|-------------|--------|
| **XSS** (Stored, Reflected, DOM) | Inject JavaScript into pages | Steal cookies, redirect, deface |
| **SQL Injection** | Inject SQL into queries | Data extraction, authentication bypass |
| **CSRF** | Forge requests from authenticated user | Perform actions as victim |
| **SSRF** | Make server request internal resources | Access internal systems |
| **LFI/RFI** | Include local/remote files | RCE, data disclosure |
| **File Upload** | Upload malicious files | RCE, malware distribution |
| **Command Injection** | Inject OS commands | Full system compromise |
| **IDOR** | Access unauthorized resources | Data breach |
| **JWT Attacks** | Manipulate JSON Web Tokens | Authentication bypass |

**API Security**:
- REST vs GraphQL
- JWT structure (header, payload, signature)
- OAuth 2.0 flows (Authorization Code, Implicit, Client Credentials)
- CORS misconfigurations
- Rate limiting
- API keys

### Prerequisites

- [x] Phases 1-7 completed (Phase 5 programming especially important)

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| PortSwigger Web Security Academy | [portswigger.net/web-security](https://portswigger.net/web-security) | Complete web security training | **The best free web security resource** | 🟢→🔴 All levels |
| OWASP Official Site | [owasp.org](https://owasp.org) | Vulnerabilities, tools, guides | The industry authority | 🟡 Intermediate |
| OWASP Juice Shop | [github.com/juice-shop/juice-shop](https://github.com/juice-shop/juice-shop) | Vulnerable web app to hack | Best hacking playground | 🟡 Intermediate |
| freeCodeCamp — Web Security Course | [YouTube](https://www.youtube.com/watch?v=BByla9tR9pY) | Web security overview | Good foundation | 🟢 Beginner |
| TryHackMe — Web Fundamentals | [tryhackme.com](https://tryhackme.com/module/web-fundamentals) | Interactive web security labs | Hands-on, guided | 🟢 Beginner |
| TryHackMe — OWASP Top 10 | [tryhackme.com](https://tryhackme.com/room/owasptop10) | OWASP Top 10 hands-on | Practical application | 🟡 Intermediate |
| HackerOne CTF | [ctf.hacker101.com](https://ctf.hacker101.com) | CTF challenges for web | Bug bounty style challenges | 🟡 Intermediate |
| PentesterLab — Web (free exercises) | [pentesterlab.com](https://pentesterlab.com/exercises) | Web security exercises | Real-world scenarios | 🟡 Intermediate |
| Google's XSS Game | [xss-game.appspot.com](https://xss-game.appspot.com) | XSS challenges | Google-made, fun | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Full Web App Pentest | Test DVWA/OWASP Juice Shop end-to-end | All web attacks |
| Automated Scanner | Build a Python script that detects SQLi and XSS | Automation, detection |
| XSS Payload Collection | Build a library of XSS payloads and test them | XSS mastery |
| Burp Suite Extension | Write a simple Burp extension in Python | Tool extensibility |
| Bug Bounty Recon Pipeline | Build automated recon scripts for targets | Recon automation |

### Labs & Exercises

- **Lab 1**: Complete ALL PortSwigger SQL injection labs (there are ~15)
- **Lab 2**: Complete ALL PortSwigger XSS labs (stored, reflected, DOM)
- **Lab 3**: Exploit CSRF on a vulnerable app
- **Lab 4**: Exploit SSRF to read internal files
- **Lab 5**: Hack the OWASP Juice Shop (try to get all flags)
- **Lab 6**: Perform a JWT attack (none algorithm, weak secret)
- **Lab 7**: Exploit file upload to get RCE on DVWA
- **Lab 8**: Complete all web challenges on TryHackMe Web Fundamentals path

### ⏱️ Estimated Time: 6-10 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I can exploit SQL injection blind and error-based
- [ ] I can exploit all three types of XSS (Stored, Reflected, DOM)
- [ ] I can use Burp Suite for intercepting, scanning, and exploiting
- [ ] I understand OAuth, JWT, and CORS security issues
- [ ] I have completed all PortSwigger labs in at least 5 categories

---

## Phase 9: Ethical Hacking & Penetration Testing

### Learning Objectives

- [ ] Execute a full penetration testing methodology
- [ ] Master reconnaissance and information gathering
- [ ] Perform vulnerability scanning and enumeration
- [ ] Exploit vulnerabilities to gain access
- [ ] Escalate privileges on Linux and Windows
- [ ] Maintain persistence and pivot
- [ ] Write professional penetration testing reports
- [ ] Understand legal and ethical boundaries

### Core Concepts

**Penetration Testing Phases**:

```
┌─────────────────────────────────────────────────┐
│ 1. Pre-engagement (Scope, ROE, Contract)        │
│ 2. Reconnaissance (Passive & Active)             │
│ 3. Scanning & Enumeration                        │
│ 4. Exploitation                                  │
│ 5. Privilege Escalation                          │
│ 6. Lateral Movement                              │
│ 7. Persistence                                   │
│ 8. Data Exfiltration (if authorized)             │
│ 9. Reporting                                     │
└─────────────────────────────────────────────────┘
```

**Essential Tools**:

| Category | Tools |
|----------|-------|
| Reconnaissance | Nmap, Masscan, Shodan, Google Dorks, TheHarvester, Recon-ng, Maltego |
| Web Enumeration | Gobuster, Dirb, FFUF, Nikto, WhatWeb, WPScan |
| Exploitation | Metasploit, Searchsploit, Manual exploitation |
| Password Attacks | Hydra, John the Ripper, Hashcat, Medusa |
| Sniffing | Wireshark, tcpdump, Responder |
| Post-Exploitation | Mimikatz, BloodHound, PowerView, SharpHound, Cobalt Strike (alternative: Covenant, Empire) |
| Tunneling | Chisel, Ligolo-ng, SSH tunneling, socat |
| Reporting | Dradis, CherryTree, KeepNote |

**Linux Privilege Escalation**:
- Kernel exploits
- SUDO misconfigurations
- SUID binaries
- Cron jobs
- Weak file permissions
- PATH hijacking
- Capabilities
- Docker/LXC groups

**Windows Privilege Escalation**:
- Kernel exploits
- Service misconfigurations
- Unquoted service paths
- Weak service permissions
- AlwaysInstallElevated
- Token impersonation
- Unattended installations
- Group Policy preferences (cPasswords)

### Prerequisites

- [x] All previous phases completed

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| TCM Security — Practical Ethical Hacking (Free portion) | [YouTube](https://www.youtube.com/watch?v=3FNYvj2U0HM) (15+ hours) | Full pentesting course | **Best free pentesting course** | 🟡 Intermediate |
| TCM Security — Linux Privilege Escalation | [YouTube](https://www.youtube.com/watch?v=dk2wsyFiosg) | Linux PE techniques | The best PE course | 🟡 Intermediate |
| TCM Security — Windows Privilege Escalation | [YouTube](https://www.youtube.com/watch?v=fB0M4M9Dqfg) | Windows PE techniques | The best PE course | 🔴 Advanced |
| IppSec (YouTube) | [YouTube Channel](https://www.youtube.com/channel/UCa6eh7gCkpPo5XXUDfygQQA) | HTB walkthroughs | Learn methodology by watching pro | 🟡→🔴 All levels |
| Hack The Box — Starting Point | [hackthebox.com](https://www.hackthebox.com/starting-point) | Beginner-friendly HTB machines | Guided, free, excellent | 🟢 Beginner |
| TryHackMe — Complete Beginner Path | [tryhackme.com](https://tryhackme.com/path/beginner) | Pentesting fundamentals | Structured learning path | 🟢 Beginner |
| TryHackMe — Jr Penetration Tester | [tryhackme.com](https://tryhackme.com/path/jrpenetrationtester) | Full pentesting path | Professional pathway | 🟡 Intermediate |
| VulnHub | [vulnhub.com](https://vulnhub.com) | Vulnerable VMs to practice | Download and hack in your lab | 🟡→🔴 All levels |
| InfoSec Prep (YouTube) | [YouTube](https://www.youtube.com/@InfoSecPrep) | OSCP preparation walkthroughs | Great for methodology | 🔴 Advanced |
| HackerSploit (YouTube) | [YouTube](https://www.youtube.com/c/HackerSploit) | Pentesting tutorials | Good for beginners | 🟢→🟡 All levels |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Home Penetration Testing Lab | Kali + targets (Metasploitable, VulnHub, HTB) | Lab building |
| Full Pentest Report | Execute a full pentest on a VulnHub machine and write a professional report | Methodology, reporting |
| Custom Exploit Development | Write a Python exploit for a known CVE | Exploit development |
| Privilege Escalation Script | Build an automated Linux PE enumeration script | PE automation |
| Pivot Lab | Set up multi-network lab and pivot through targets | Lateral movement |

### Labs & Exercises

- **Lab 1**: Complete TJ_Null's OSCP list (free machines from VulnHub/HTB)
- **Lab 2**: Hack at least 5 machines from Hack The Box starting point
- **Lab 3**: Complete the TryHackMe Jr Penetration Tester path
- **Lab 4**: Perform a full pentest on Kioptrix series (VulnHub)
- **Lab 5**: Set up a multi-subnet lab and practice pivoting
- **Lab 6**: Perform Active Directory attack chain (LLMNR poisoning → NTLMv2 hash capture → cracking → lateral movement → DA)

### ⏱️ Estimated Time: 8-12 weeks 🔴

### 🏁 Milestone Before Moving On

- [ ] I can perform a full penetration test from recon to reporting
- [ ] I can escalate privileges on both Linux and Windows
- [ ] I can use Metasploit effectively but also exploit manually
- [ ] I understand Active Directory attack paths
- [ ] I have written at least 3 professional penetration testing reports

---

## Phase 10: Digital Forensics & Incident Response

### Learning Objectives

- [ ] Understand forensic methodology and chain of custody
- [ ] Perform disk forensics (acquire, analyze, report)
- [ ] Perform memory forensics (capture, analyze)
- [ ] Analyze log files for evidence
- [ ] Use Autopsy and Volatility effectively
- [ ] Understand the incident response lifecycle
- [ ] Perform threat hunting

### Core Concepts

**Digital Forensics Methodology**:
```
1. Identification — Detect the incident
2. Preservation — Secure the evidence, create forensic images
3. Collection — Gather data (disk, memory, logs, network)
4. Examination — Analyze the data
5. Analysis — Draw conclusions
6. Reporting — Document findings
```

**Chain of Custody** — Document every person who handles evidence. Break chain = evidence inadmissible.

**Disk Forensics**:
- Forensic images (dd, Guymager, FTK Imager)
- Filesystem analysis (NTFS, FAT, ext4)
- File carving (recover deleted files)
- Steganalysis
- Timeline analysis

**Memory Forensics**:
- Memory acquisition (FTK Imager, LiME, DumpIt)
- Volatility profiles
- Process listing
- Network connections
- Registry hives in memory
- Extract malware from memory

**Log Analysis**:
- Windows Event Logs (Event IDs)
- Linux logs (/var/log)
- Web server logs
- Firewall logs
- SIEM correlation

**Incident Response Lifecycle** (NIST SP 800-61):

```
Preparation → Detection & Analysis → Containment → Eradication → Recovery → Post-Incident
```

### Prerequisites

- [x] Phases 1-9 recommended

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| 13Cubed (YouTube) | [YouTube Channel](https://www.youtube.com/c/13cubed) | DFIR tutorials | Best forensics channel | 🟡→🔴 All levels |
| freeCodeCamp — Digital Forensics (by 13Cubed) | [YouTube](https://www.youtube.com/watch?v=RYIXvurCQQQ) | Full forensics course | 5-hour comprehensive course | 🟡 Intermediate |
| CFSO — Digital Forensics | [cyberforensic.org](https://cyberforensic.org) | Forensics resources | Community-contributed | 🟡 Intermediate |
| TryHackMe — Digital Forensics Path | [tryhackme.com](https://tryhackme.com/module/digital-forensics) | Forensics labs | Interactive, hands-on | 🟢 Beginner |
| TryHackMe — Intro to Digital Forensics | [tryhackme.com](https://tryhackme.com/room/introdigitalforensics) | Forensics fundamentals | Good starting point | 🟢 Beginner |
| Volatility Foundation | [volatilityfoundation.org](https://www.volatilityfoundation.org) | Memory forensics docs | Official Volatility resources | 🟡 Intermediate |
| SANS DFIR Poster | [sans.org/security-resources/posters/dfir/](https://www.sans.org/security-resources/posters/dfir/) | DFIR cheat sheets | Excellent quick reference | 🟡 Intermediate |
| CyberDefenders | [cyberdefenders.org](https://cyberdefenders.org) | Blue Team CTF labs | Practice forensics challenges | 🟡 Intermediate |
| DFIR Madness | [youtube.com/@DFIRMadness](https://www.youtube.com/@DFIRMadness) | Practical DFIR tutorials | Real case walkthroughs | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Forensic Image Analysis | Download a forensic image and analyze it with Autopsy | Disk forensics |
| Memory Capture & Analysis | Capture a VM's memory and analyze with Volatility | Memory forensics |
| Log Analysis Dashboard | Build a Python/SIEM dashboard for analyzing security logs | Log analysis |
| Incident Response Playbook | Write IR playbooks for ransomware, phishing, data breach | IR methodology |
| Timeline Analysis | Build a timeline of events from disk image + memory + logs | Correlation |

### Labs & Exercises

- **Lab 1**: Use Autopsy to analyze a forensic image (find files, deleted data, metadata)
- **Lab 2**: Capture memory from a VM and analyze it with Volatility (list processes, network connections, extract malware)
- **Lab 3**: Analyze Windows Event Logs to trace an attacker's activity
- **Lab 4**: Perform timeline analysis using Plaso (log2timeline)
- **Lab 5**: Recover deleted files from a disk image using file carving
- **Lab 6**: Complete the TryHackMe Digital Forensics path (at least 5 rooms)
- **Lab 7**: Analyze a network PCAP for signs of compromise
- **Lab 8**: Write a full incident response report for a simulated breach

### ⏱️ Estimated Time: 6-8 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I can acquire and analyze a forensic disk image
- [ ] I can capture and analyze memory with Volatility
- [ ] I understand chain of custody and forensic procedures
- [ ] I can analyze event logs for security incidents
- [ ] I know the incident response lifecycle

---

## Phase 11: Malware Analysis & Reverse Engineering

### Learning Objectives

- [ ] Understand malware types and behaviors
- [ ] Perform static analysis of malware samples
- [ ] Perform dynamic analysis in a sandbox
- [ ] Use disassemblers and debuggers (Ghidra, x64dbg)
- [ ] Understand PE file structure
- [ ] Analyze network indicators of compromise (IOCs)
- [ ] Write basic signatures (YARA rules)

### Core Concepts

**Malware Classification**:
- Virus, Worm, Trojan, Ransomware, Spyware, RAT, Rootkit
- Fileless malware
- Macro malware
- Bootkits
- Botnets

**Analysis Approaches**:

| Type | What It Involves | Tools |
|------|-----------------|-------|
| **Static** | Analyze without executing | strings, PEview, Detect It Easy, Ghidra |
| **Dynamic** | Execute in sandbox and observe | Cuckoo, CAPE, ProcMon, Wireshark, API Monitor |
| **Reverse Engineering** | Decompile/disassemble to understand logic | Ghidra, IDA Free, x64dbg, dnSpy |

**PE (Portable Executable) Structure**:
- DOS Header
- NT Headers (File Header, Optional Header)
- Section Headers (.text, .data, .rdata, .rsrc)
- Import/Export tables
- Resources

**Indicators of Compromise (IOCs)**:
- File hashes (MD5, SHA-1, SHA-256)
- IP addresses
- Domain names
- Registry keys
- File paths
- Mutexes
- YARA rules

**YARA Rules**:
```
rule SuspiciousString
{
    strings:
        $a = "CreateRemoteThread" nocase
        $b = "VirtualAllocEx" nocase
    condition:
        all of them
}
```

### Prerequisites

- [x] Phases 1-8 completed (strong C/Assembly knowledge helpful)
- [x] Understanding of x86/x64 assembly (minimal)

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| OALABS (YouTube) | [YouTube](https://www.youtube.com/@OALABS) | Reverse engineering tutorials | Modern, practical RE | 🔴 Advanced |
| OpenSecurityTraining | [opensecuritytraining.info](https://opensecuritytraining.info) | Intro to Reverse Engineering | Academic-quality free training | 🟡→🔴 All levels |
| Tuts 4 You | [tuts4you.com](https://tuts4you.com) | Reverse engineering tutorials | Huge collection of RE resources | 🔴 Advanced |
| Malware Unicorn — Reverse Engineering Malware 101 | [malwareunicorn.org](https://malwareunicorn.org/#/workshops) | Malware RE workshop | Step-by-step, excellent | 🟡 Intermediate |
| Ghidra 101 (YouTube) | [YouTube Playlist](https://www.youtube.com/playlist?list=PL_h5QJX7hYTAhD3mk3fjQ9sx6PCqUU9PS) | Ghidra using for RE | Best Ghidra tutorials | 🟡 Intermediate |
| TryHackMe — Malware Analysis | [tryhackme.com](https://tryhackme.com/module/malware-analysis) | Malware analysis labs | Hands-on, guided | 🟡 Intermediate |
| VX Underground | [vx-underground.org](https://vx-underground.org) | Malware samples and papers | Extensive malware library | 🔴 Advanced |
| The ZOO (Malware DB) | [thezoo.morirt.com](https://thezoo.morirt.com) | Malware samples | Curated malware collection | 🔴 Advanced |
| ANY.RUN (Free Tier) | [any.run](https://any.run) | Online malware sandbox | Interactive, no setup needed | 🟢 Beginner |
| Hybrid Analysis (Free) | [hybrid-analysis.com](https://hybrid-analysis.com) | Automated malware analysis | Submit and get instant report | 🟢 Beginner |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Static Analysis Report | Analyze a real malware sample (static only) | Static analysis, YARA |
| Dynamic Analysis Report | Run malware in sandbox and document behavior | Dynamic analysis |
| YARA Rule Set | Create YARA rules for a specific malware family | Signature creation |
| Ghidra Script | Write a Ghidra script to automate analysis | Reverse engineering |
| Malware Classification Tool | Build a script that classifies samples by behavior | Analysis automation |

### Labs & Exercises

- **Lab 1**: Use `strings`, PEview, and Detect It Easy to perform static analysis on a sample
- **Lab 2**: Analyze a malware sample in ANY.RUN and document all IOCs
- **Lab 3**: Use Ghidra to decompile a simple crackme and understand the algorithm
- **Lab 4**: Create YARA rules for the Trickbot malware family
- **Lab 5**: Perform dynamic analysis — run malware in a VM with ProcMon, Wireshark, Regshot
- **Lab 6**: Debug a simple executable with x64dbg and analyze its behavior
- **Lab 7**: Unpack a packed binary (UPX)

### ⏱️ Estimated Time: 8-12 weeks 🔴

### 🏁 Milestone Before Moving On

- [ ] I can perform static analysis on a PE file
- [ ] I can use Ghidra for basic reverse engineering
- [ ] I can write YARA rules
- [ ] I understand the PE file structure
- [ ] I can safely sandbox and analyze a malware sample

---

## Phase 12: Cloud Security

### Learning Objectives

- [ ] Understand AWS and Azure core services
- [ ] Configure IAM policies and roles securely
- [ ] Secure cloud networking (VPC, Security Groups, NSGs)
- [ ] Understand shared responsibility model
- [ ] Monitor cloud environments for threats
- [ ] Identify cloud-specific vulnerabilities
- [ ] Perform cloud penetration testing

### Core Concepts

**Shared Responsibility Model**:

```
┌─────────────────────────────────────┐
│ On-Premises: YOU manage everything   │
├─────────────────────────────────────┤
│ IaaS: You manage OS, app, data       │
│       Cloud manages virtualization    │
├─────────────────────────────────────┤
│ PaaS: You manage app & data           │
│       Cloud manages rest              │
├─────────────────────────────────────┤
│ SaaS: You manage data & users         │
│       Cloud manages everything else   │
└─────────────────────────────────────┘
```

**AWS Fundamentals**:
- EC2, S3, Lambda, VPC, IAM, CloudTrail, CloudWatch
- Security Groups vs NACLs
- S3 bucket policies
- IAM users, groups, roles, policies
- AWS KMS encryption
- CloudTrail logging

**Azure Fundamentals**:
- Virtual Machines, Blob Storage, Functions, VNet
- Azure AD (Entra ID)
- RBAC vs Azure Policies
- NSGs and ASGs
- Azure Security Center (Defender for Cloud)
- Sentinel (SIEM)

**Cloud Threats**:
- Misconfigured S3 buckets
- Overly permissive IAM roles
- Insecure APIs
- Exposed credentials (hardcoded API keys)
- Privilege escalation (IAM)
- Data exfiltration
- Account takeover

**Tools**:
- ScoutSuite (cloud auditing)
- Pacu (AWS exploitation framework)
- Cloudsplaining (IAM analysis)
- Prowler (cloud security assessment)
- Stratus Red Team (cloud attack simulation)

### Prerequisites

- [x] Phases 1-8 completed
- [x] Networking fundamentals

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| AWS Free Tier + Learn | [aws.amazon.com/free](https://aws.amazon.com/free) + [learn.aws.dev](https://learn.aws.dev) | AWS fundamentals | Hands-on, free tier | 🟢 Beginner |
| Microsoft Learn — Azure Security | [learn.microsoft.com](https://learn.microsoft.com/en-us/training/security/) | Azure security | Official, structured | 🟢 Beginner |
| freeCodeCamp — AWS Certified Cloud Practitioner | [YouTube](https://www.youtube.com/watch?v=SOTamWNgDKc) | AWS fundamentals | Complete course | 🟢 Beginner |
| freeCodeCamp — Azure Security | [YouTube](https://www.youtube.com/watch?v=Vp5CBhzwjVM) | Azure security overview | Good overview | 🟡 Intermediate |
| TryHackMe — Cloud Security | [tryhackme.com](https://tryhackme.com/module/cloud-security) | Cloud security labs | Hands-on AWS/Azure | 🟡 Intermediate |
| Flaws.cloud | [flaws.cloud](http://flaws.cloud) | AWS security challenges | CTF for cloud security | 🟡 Intermediate |
| Flaws2.cloud | [flaws2.cloud](http://flaws2.cloud) | Advanced AWS challenges | Continue from Flaws | 🔴 Advanced |
| CloudGoat | [github.com/RhinoSecurityLabs/cloudgoat](https://github.com/RhinoSecurityLabs/cloudgoat) | Vulnerable AWS infrastructure | Practice exploitation | 🔴 Advanced |
| AWS Well-Architected Framework | [docs.aws.amazon.com/wellarchitected](https://docs.aws.amazon.com/wellarchitected) | Security best practices | Industry-standard framework | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| AWS Security Lab | Deploy a 3-tier app on AWS and secure it | IAM, VPC, SG |
| Cloud Audit Pipeline | Set up CloudTrail + alerts for security events | Monitoring |
| Serverless App Security | Build a serverless API with proper auth | Lambda, API Gateway |
| CloudGoat Walkthrough | Exploit all CloudGoat scenarios | Cloud exploitation |

### Labs & Exercises

- **Lab 1**: Create a free AWS account and set up IAM users with MFA
- **Lab 2**: Deploy an EC2 instance in a VPC with proper security groups
- **Lab 3**: Set up S3 bucket with proper policies (and intentionally misconfigure one)
- **Lab 4**: Use ScoutSuite to audit your AWS environment
- **Lab 5**: Complete Flaws.cloud challenges (all levels)
- **Lab 6**: Set up CloudTrail + CloudWatch for monitoring
- **Lab 7**: Use Pacu to exploit an intentionally vulnerable AWS environment (CloudGoat)

### ⏱️ Estimated Time: 4-8 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I understand the shared responsibility model
- [ ] I can configure IAM with least privilege
- [ ] I understand VPC, Security Groups, and NACLs
- [ ] I can identify common cloud misconfigurations
- [ ] I have completed Flaws.cloud challenges

---

## Phase 13: Containers & DevSecOps

### Learning Objectives

- [ ] Understand Docker and container security
- [ ] Understand Kubernetes and K8s security
- [ ] Implement DevSecOps practices
- [ ] Secure CI/CD pipelines
- [ ] Use container security scanning tools
- [ ] Harden container environments

### Core Concepts

**Docker Security**:
- Container isolation (namespaces, cgroups)
- Running as non-root
- Read-only root filesystem
- No new privileges
- Securing images (no secrets in layers)
- Docker Bench Security
- Image scanning (Trivy, Clair)

**Kubernetes Security**:
- RBAC
- Pod Security Policies / Pod Security Standards
- Network policies
- Secrets management
- Service accounts
- Admission controllers
- Namespace isolation
- etcd encryption

**DevSecOps**:
- "Shift left" — security early in development
- SAST (Static Application Security Testing)
- DAST (Dynamic Application Security Testing)
- SCA (Software Composition Analysis)
- Secrets scanning
- CI/CD pipeline security
- Infrastructure as Code (IaC) scanning

**Tools**:
- Docker Bench Security
- Trivy / Clair / Anchore (image scanning)
- kube-bench / kube-hunter (K8s security)
- OPA / Gatekeeper (policy as code)
- SonarQube (SAST)
- Checkov / tfsec (IaC scanning)
- GitLeaks / TruffleHog (secrets scanning)

### Prerequisites

- [x] Phases 1-8 completed

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Docker Curriculum | [docker-curriculum.com](https://docker-curriculum.com) | Docker from scratch | Comprehensive, hands-on | 🟢 Beginner |
| freeCodeCamp — Docker Course | [YouTube](https://www.youtube.com/watch?v=9Z6uLHMQkGQ) | Docker complete guide | 4-hour deep dive | 🟢 Beginner |
| freeCodeCamp — Kubernetes Course | [YouTube](https://www.youtube.com/watch?v=X48VuDVv0do) | K8s from scratch | 5-hour comprehensive | 🟡 Intermediate |
| Kubernetes Official Documentation | [kubernetes.io/docs](https://kubernetes.io/docs) | K8s reference | The official source | 🟡 Intermediate |
| TryHackMe — Container Security | [tryhackme.com](https://tryhackme.com/room/containersecurity) | Container security labs | Hands-on | 🟡 Intermediate |
| Docker Security Documentation | [docs.docker.com/engine/security/](https://docs.docker.com/engine/security/) | Docker security best practices | Official guide | 🟡 Intermediate |
| OWASP DevSecOps | [owasp.org/www-project-devsecops](https://owasp.org/www-project-devsecops) | DevSecOps guidelines | Industry standard | 🟡 Intermediate |
| GrappleCon (YouTube) | [YouTube](https://www.youtube.com/@GrappleCon) | Container security talks | Latest trends and threats | 🟡→🔴 All levels |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Docker Hardening | Create a secure Dockerfile for a web app with all best practices | Docker security |
| Kubernetes Security Audit | Use kube-bench and kube-hunter on a cluster | K8s security |
| CI/CD Pipeline with Security | Build a GitHub Actions pipeline with SAST + image scanning | DevSecOps pipeline |
| Container Escape Lab | Practice container escape techniques (in a lab VM!) | Container threats |
| IaC Scanner | Use Checkov to scan Terraform files for misconfigurations | IaC security |

### Labs & Exercises

- **Lab 1**: Install Docker and run your first container (non-root)
- **Lab 2**: Run Docker Bench Security and fix 10+ findings
- **Lab 3**: Scan a Docker image with Trivy and fix vulnerabilities
- **Lab 4**: Set up a mini Kubernetes cluster (Minikube or kind)
- **Lab 5**: Run kube-bench and remediate findings
- **Lab 6**: Implement network policies in Kubernetes
- **Lab 7**: Set up a GitHub Actions pipeline that scans code for secrets

### ⏱️ Estimated Time: 4-6 weeks 🟡

### 🏁 Milestone Before Moving On

- [ ] I can create secure Docker images
- [ ] I understand Kubernetes RBAC and network policies
- [ ] I can use Trivy to scan images for vulnerabilities
- [ ] I can set up basic DevSecOps pipeline
- [ ] I can use IaC scanning tools

---

## Phase 14: Security Operations (Blue Team)

### Learning Objectives

- [ ] Understand SIEM architecture and use cases
- [ ] Set up and configure a SIEM (Splunk, Wazuh, ELK)
- [ ] Create detection rules and alerts
- [ ] Understand SOC operations and tier model
- [ ] Perform threat hunting
- [ ] Detect and respond to common attacks
- [ ] Understand threat intelligence and IoCs

### Core Concepts

**SIEM (Security Information and Event Management)**:
- Log collection (agents, syslog, WinRM)
- Log parsing and normalization
- Correlation rules
- Alerting and dashboard
- Compliance reporting

**SOC (Security Operations Center)**:

| Tier | Role | Responsibilities |
|------|------|-----------------|
| Tier 1 | Triage Analyst | Monitor alerts, initial triage, escalate |
| Tier 2 | Incident Responder | Investigate, contain, remediate |
| Tier 3 | Threat Hunter/SME | Deep analysis, threat hunting, forensics |

**Detection Engineering**:
- Sigma rules (generic detection format)
- SNORT/Suricata rules (network IDS)
- YARA rules (file/memory detection)
- QUERY rules (KQL, SPL, EQL)

**Threat Intelligence**:
- OSINT
- MITRE ATT&CK Framework
- Threat feeds (MISP, AlienVault OTX)
- IoC sharing
- Diamond Model

**Tools**:

| Tool | Use Case | Free? |
|------|----------|-------|
| Splunk Free | Full SIEM (500MB/day) | ✅ Limited |
| Wazuh | Open-source SIEM + XDR | ✅ Completely |
| ELK Stack (Elastic Security) | SIEM + detection | ✅ Limited |
| Security Onion | Complete Linux distro for defending | ✅ Completely |
| TheHive + Cortex | Incident response platform | ✅ Completely |
| MISP | Threat intelligence platform | ✅ Completely |
| Snort/Suricata | Network IDS/IPS | ✅ Completely |
| Velociraptor | Endpoint monitoring, DFIR | ✅ Completely |

### Prerequisites

- [x] Phases 1-10 recommended (especially forensics)

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| Splunk Free — Tutorials | [splunk.com](https://www.splunk.com/en_us/training/free-certification-online-splunk-training.html) | Splunk SPL and dashboards | Industry standard SIEM | 🟡 Intermediate |
| Wazuh Documentation | [documentation.wazuh.com](https://documentation.wazuh.com) | Open-source SIEM setup | Completely free, comprehensive | 🟡 Intermediate |
| TryHackMe — SOC Path | [tryhackme.com](https://tryhackme.com/module/soc) | SOC operations labs | Hands-on SOC skills | 🟡 Intermediate |
| TryHackMe — Cyber Defense Path | [tryhackme.com](https://tryhackme.com/path/defensive) | Blue team complete path | Comprehensive defense training | 🟡 Intermediate |
| BlueTeamLabs Online | [blueteamlabs.online](https://blueteamlabs.online) | Blue team CTF challenges | Practice incident response | 🟡 Intermediate |
| Security Onion Documentation | [docs.securityonion.net](https://docs.securityonion.net) | Setting up Security Onion | Best free defense platform | 🟡 Intermediate |
| MITRE ATT&CK | [attack.mitre.org](https://attack.mitre.org) | Adversary tactics and techniques | The industry framework | 🟡 Intermediate |
| CyberDefenders — Blue Team Challenges | [cyberdefenders.org](https://cyberdefenders.org) | DFIR challenges | Excellent practice | 🟡→🔴 All levels |
| Sigma Rules GitHub | [github.com/SigmaHQ/sigma](https://github.com/SigmaHQ/sigma) | Generic detection rules | Write your own detection | 🟡 Intermediate |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Wazhomelab | Set up Wazuh SIEM at home | SIEM installation, configuration |
| Custom Detection Rule | Write Sigma rules for specific attack detection | Detection engineering |
| SOC Dashboard | Build a Splunk/Wazuh dashboard for security monitoring | Visualization |
| Threat Intel Feed | Set up MISP and ingest threat intel | Threat intelligence |
| Incident Response Report | Write a full IR report for a simulated attack | IR documentation |

### Labs & Exercises

- **Lab 1**: Install Wazuh and add an agent to a Windows machine
- **Lab 2**: Create a custom detection rule in Wazuh (e.g., detect mimikatz usage)
- **Lab 3**: Install Security Onion and analyze network traffic
- **Lab 4**: Use Velociraptor to collect forensic artifacts from endpoints
- **Lab 5**: Install MISP and add threat intel feeds
- **Lab 6**: Complete the TryHackMe SOC Tier 1 path
- **Lab 7**: Write Sigma rules for common attack techniques (e.g., PowerShell abuse)
- **Lab 8**: Perform threat hunting using MITRE ATT&CK framework

### ⏱️ Estimated Time: 6-10 weeks 🟠

### 🏁 Milestone Before Moving On

- [ ] I can install and configure Wazuh or ELK SIEM
- [ ] I can write Sigma rules for detection
- [ ] I understand SOC tier structure
- [ ] I can perform basic threat hunting
- [ ] I understand MITRE ATT&CK framework and can map attacks to it

---

## Phase 15: Advanced Red Teaming

### Learning Objectives

- [ ] Execute advanced Active Directory attacks
- [ ] Understand Kerberos attacks in depth
- [ ] Use C2 frameworks (Covenant, Empire, Sliver)
- [ ] Implement OPSEC and evasion techniques
- [ ] Perform physical security assessments
- [ ] Understand social engineering
- [ ] Write custom tooling

### Core Concepts

**Active Directory Attack Paths**:

| Technique | Description |
|-----------|-------------|
| LLMNR/NBT-NS Poisoning | Respond to failed DNS queries to capture hashes |
| SMB Relay | Relay captured NTLM hashes to other machines |
| Kerberoasting | Request TGS for service accounts and crack offline |
| AS-REP Roasting | Find users without pre-auth and crack their hashes |
| Pass-the-Hash | Use NTLM hash to authenticate without password |
| Pass-the-Ticket | Use Kerberos ticket for authentication |
| Golden Ticket | Forge a TGT (need KRBTGT hash) |
| Silver Ticket | Forge a TGS for a specific service |
| DCSync | Replicate domain controller data (get all hashes) |
| ACL Abuse | Abuse delegated permissions for privilege escalation |
| Unconstrained Delegation | Steal TGT of other users |
| Constrained Delegation | Abuse delegation trusts |

**C2 Frameworks**:

| Framework | Features | Free? |
|-----------|----------|-------|
| Covenant | .NET-based, modern UI | ✅ Completely |
| Empire | PowerShell/post-exploitation | ✅ Completely |
| Sliver | Go-based, modern | ✅ Completely |
| Cobalt Strike | Industry standard (expensive) | ❌ Paid |
| Havoc | Modern C2 | ✅ Completely |

**OPSEC (Operational Security)**:
- Payload obfuscation
- Living off the land (LOLBins)
- Traffic encryption and mimicry
- Sleep timers and jitter
- Process injection techniques
- AMSI bypass
- Defender/AV evasion
- Log clearing (carefully)
- Redirectors and domain fronting

**Social Engineering**:
- Phishing (spear phishing, whaling)
- Vishing (voice phishing)
- Pretexting
- USB drop attacks
- Physical tailgating

### Prerequisites

- [x] All previous Phases 1-14 recommended
- [x] Strong AD knowledge

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| TCM Security — Practical Windows AD Attacks (Free portions) | [YouTube](https://www.youtube.com/watch?v=G2QJ9JsOAn8) | AD attack techniques | Best free AD security course | 🔴 Advanced |
| TCM Security — External Pentest Playbook | [YouTube](https://www.youtube.com/watch?v=Y7U6Ri7Y7v8) | External penetration testing | Methodology deep dive | 🔴 Advanced |
| SpecterOps Blog | [posts.specterops.io](https://posts.specterops.io) | Advanced AD attacks | Industry leading research | 🔴 Advanced |
| The Hacker Recipes | [thehacker.recipes](https://www.thehacker.recipes) | Technical guides | Comprehensive red team guides | 🔴 Advanced |
| Al14s Security (YouTube) | [YouTube](https://www.youtube.com/@Al14s) | Red team techniques | Modern techniques explained | 🔴 Advanced |
| Rana Khalil (YouTube) | [YouTube](https://www.youtube.com/@RanaKhalil) | Pentesting walkthroughs | Great methodology | 🔴 Advanced |
| TryHackMe — Red Team Path | [tryhackme.com](https://tryhackme.com/path/redteam) | Red teaming labs | Structured red team path | 🔴 Advanced |
| Hack The Box — Active Directory Track | [hackthebox.com](https://www.hackthebox.com) | AD pentesting machines | Realistic AD environments | 🔴 Advanced |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Full AD Attack Lab | Build a domain, attack it from zero to domain admin | AD attack chain |
| Custom C2 Implant | Build a simple beacon (Python or Nim) | C2 development |
| Phishing Campaign Lab | Set up GoPhish and run a simulated campaign | Social engineering |
| OPSEC Toolkit | Build obfuscated payloads using different techniques | Evasion |
| Red Team Report | Execute a full red team engagement and report | Reporting |

### Labs & Exercises

- **Lab 1**: Build a complete AD lab with multiple DCs, servers, workstations
- **Lab 2**: Execute the full AD attack chain (LLMNR → hash capture → cracking → lateral → DA)
- **Lab 3**: Set up Covenant C2 and deploy an implant
- **Lab 4**: Perform Kerberoasting and AS-REP roasting against your domain
- **Lab 5**: Execute DCSync attack (in your own lab only!)
- **Lab 6**: Bypass Windows Defender with custom obfuscation
- **Lab 7**: Create a phishing email campaign with GoPhish
- **Lab 8**: Practice evading detection (AMSI bypass, event log manipulation)

### ⏱️ Estimated Time: 10-16 weeks ⚫

### 🏁 Milestone Before Moving On

- [ ] I can execute a full AD attack chain from zero to domain admin
- [ ] I can set up and use a C2 framework (Covenant or Sliver)
- [ ] I understand OPSEC and evasion techniques
- [ ] I can bypass common antivirus/EDR
- [ ] I can write custom tooling for specific tasks

---

## Phase 16: Bug Bounty Hunting

### Learning Objectives

- [ ] Understand bug bounty methodology and scope
- [ ] Build a recon pipeline
- [ ] Identify and exploit common web vulnerabilities
- [ ] Write professional bug bounty reports
- [ ] Understand disclosure processes
- [ ] Manage time and targets effectively
- [ ] Automate reconnaissance

### Core Concepts

**Bug Bounty Methodology**:

```
1. Choose a Target (scope: *.example.com)
2. Reconnaissance (subdomains, endpoints, tech stack)
3. Mapping (understand functionality)
4. Vulnerability Detection (manual + automated)
5. Exploitation (prove impact)
6. Reporting (clear, reproducible, impacted)
7. Disclosure (follow program guidelines)
```

**Recon Pipeline**:

```
Subdomain Enumeration → Port Scanning → Web Screenshotting → Tech Detection → Endpoint Discovery → Parameter Fuzzing
```

**Tools**:

| Tool | Purpose |
|------|---------|
| Subfinder / Amass | Subdomain discovery |
| httpx | Check live hosts |
| nuclei | Vulnerability scanning |
| Katana / gospider | Crawling and endpoint discovery |
| ffuf / gobuster | Directory/parameter fuzzing |
| Burp Suite | Intercepting proxy, scanning |
| dalfox | XSS scanning |
| sqlmap | SQL injection automation |
| naabu | Port scanning |

**Reporting**:
- Clear, concise, professional
- Steps to reproduce (STR)
- Impact explanation
- Proof of Concept (PoC) — screenshots, video, code
- Bounty expectations

**Responsible Disclosure**:
- 90-day disclosure window (standard)
- Notify vendor first
- Publish only after fix
- CVE assignment

### Prerequisites

- [x] All previous phases (especially Web Security, Phase 8)
- [x] Python programming

### Free Resources

| Resource | Link | What It Teaches | Why Recommended | Difficulty |
|----------|------|-----------------|-----------------|------------|
| HackerOne 101 | [hackerone.com](https://www.hackerone.com/hackers/hacker101) | Bug hunting fundamentals | Official HackerOne course | 🟡 Intermediate |
| PortSwigger Web Security Academy | [portswigger.net/web-security](https://portswigger.net/web-security) | Full web security training | **The best free resource** | 🟡 Intermediate |
| TomNomNom (YouTube/Talks) | [YouTube](https://www.youtube.com/@TomNomNom) | Recon techniques | Learn from one of the best | 🔴 Advanced |
| STÖK on Bug Bounty (YouTube) | [YouTube](https://www.youtube.com/@STOKfredrik) | Bug bounty methodology | Real bug bounty videos | 🟡 Intermediate |
| InsiderPhD (YouTube) | [YouTube](https://www.youtube.com/@InsiderPhD) | Bug bounty guides | Great for beginners | 🟢 Beginner |
| NahamSec (YouTube) | [YouTube](https://www.youtube.com/@NahamSec) | Bug bounty recon | Recon-focused content | 🟡 Intermediate |
| Bugcrowd University | [bugcrowd.com](https://www.bugcrowd.com/hackers/bugcrowd-university/) | Bug bounty training | Free training from Bugcrowd | 🟡 Intermediate |
| PentesterLab (Free Exercises) | [pentesterlab.com](https://pentesterlab.com) | Web security exercises | Hands-on practice | 🟡 Intermediate |
| HackerOne CTF | [ctf.hacker101.com](https://ctf.hacker101.com) | CTF challenges | Practice in CTF settings | 🟡 Intermediate |
| Bug Bounty Reports Explained | [medium.com](https://medium.com/bug-bounty-hunting) | Read real reports | Learn from real bugs | 🟡 Intermediate |

### Bug Bounty Platforms (Free to join)

| Platform | Link | Best For |
|----------|------|----------|
| HackerOne | [hackerone.com](https://www.hackerone.com) | Web & mobile, large programs |
| Bugcrowd | [bugcrowd.com](https://www.bugcrowd.com) | Diverse programs |
| Intigriti | [intigriti.com](https://www.intigriti.com) | EU-focused programs |
| YesWeHack | [yeswehack.com](https://www.yeswehack.com) | European market |
| OpenBugBounty | [openbugbounty.org](https://www.openbugbounty.org) | Disclosure-only (no money) |
| Huntr (by Protect AI) | [huntr.dev](https://www.huntr.dev) | AI/ML security bugs |

### Recommended Projects

| Project | Description | Skills Built |
|---------|-------------|-------------|
| Bug Bounty Recon Pipeline | Build automated recon scripts with notifications | Automation |
| Bug Bounty Report Template | Create a professional report template | Reporting |
| Custom Vulnerability Scanner | Build a focused scanner for a specific vuln type | Python, automation |
| Write 3 Bug Bounty Reports | Find and report vulnerabilities on VDP (Vulnerability Disclosure) programs | Full methodology |
| blog walkthroughs | Publish 5+ bug bounty writeups on Medium/your blog | Documentation, reputation |

### Labs & Exercises

- **Lab 1**: Build a complete recon pipeline (subfinder → httpx → nuclei → screenshot)
- **Lab 2**: Find 10 subdomains of a program (passive recon only)
- **Lab 3**: Use nuclei to scan for vulnerabilities on a target
- **Lab 4**: Find and exploit an XSS on a VDP program
- **Lab 5**: Submit a report to a VDP program
- **Lab 6**: Read 20+ published bug bounty reports and analyze methodology

### ⏱️ Estimated Time: Ongoing (12+ months to be consistent)

### 🏁 Milestone Before Moving On

- [ ] I have a functioning recon pipeline
- [ ] I have found and reported at least 1 valid vulnerability
- [ ] I can write professional bug reports
- [ ] I understand scope and rules of engagement

---

## Certification Roadmap

### The Optimal Certification Path

```
                ┌──────────────────────────┐
                │ Google Cybersecurity Cert  │
                │ (Beginner, Free audit)    │
                └────────────┬─────────────┘
                             │
                ┌──────────────────────────┐
                │ ISC2 Certified in Cyber  │
                │ Security (CC) — Free     │
                └────────────┬─────────────┘
                             │
                ┌──────────────────────────┐
                │ CompTIA Security+        │
                │ (Industry gateway)       │
                └────────────┬─────────────┘
                             │
              ┌──────────────┼──────────────┐
              │                             │
              ▼                             ▼
   ┌────────────────────┐       ┌────────────────────┐
   │ eJPT                │       │ Blue Team:          │
   │ (Practical, cheap)  │       │ Security Blue       │
   │                     │       │ Level 1 + 2         │
   └────────┬───────────┘       └────────┬───────────┘
            │                            │
            ▼                            ▼
   ┌────────────────────┐       ┌────────────────────┐
   │ PNPT (Practical)   │       │ CySA+ / BTL1       │
   │ AD-focused         │       │ (Blue Team certs)  │
   └────────┬───────────┘       └────────┬───────────┘
            │                            │
            └──────────────┬─────────────┘
                           │
                           ▼
                ┌──────────────────────────┐
                │ OSCP (Gold Standard)      │
                │ (Red Team)                │
                └────────────┬─────────────┘
                             │
                ┌──────────────────────────┐
                │ CISSP (Senior Role)      │
                │ (Mgmt & Strategy)        │
                └──────────────────────────┘
```

### Certification Details

| Cert | Cost | Difficulty | When to Take | What It Proves |
|------|------|------------|--------------|----------------|
| **Google Cybersecurity Cert** | Free (audit) / ~$50/mo | 🟢 Very Easy | Month 0-2 | You know security fundamentals |
| **ISC2 CC** | **FREE** (fee waived) | 🟢 Easy | Month 2-3 | You understand security principles |
| **CompTIA Security+** | ~$392 | 🟡 Moderate | Month 4-6 | Industry baseline knowledge |
| **eJPT (eLearnSecurity)** | ~$200 | 🟡 Moderate | Month 6-8 | Practical penetration testing |
| **Security Blue BTL1** | ~$350 | 🟡 Moderate | Month 6-10 | Blue team / SOC skills |
| **PNPT (TCM Security)** | ~$400 | 🔴 Hard | Month 8-12 | Practical AD pentesting |
| **CompTIA CySA+** | ~$392 | 🟡 Moderate | Month 8-12 | Blue team analysis |
| **OSCP (Offensive Security)** | ~$1,599 | ⚫ Very Hard | Month 12-18 | Pentesting gold standard |
| **CISSP (ISC2)** | ~$749 | ⚫ Very Hard | 18-24+ months | Senior security professional |

### CEH — Should You Take It?

**The Honest Truth**:

| Pros | Cons |
|------|------|
| Widely recognized by HR | Extremely expensive ($1,199+) |
| Meets DoD 8570 requirements | Multiple-choice only — no practical |
| Good for government jobs | Contains outdated material |
| | Mocked in the infosec community |
| | Better practical alternatives exist (OSCP, PNPT) |

**Verdict**: Take CEH only if:
1. You need DoD 8570 compliance (US government jobs)
2. Your employer pays for it
3. You want to work in consulting where clients demand it

Otherwise **skip CEH** and go for PNPT → OSCP.

---

## Career Tracks

### 1. Penetration Tester

| Aspect | Details |
|--------|---------|
| **Core Skills** | Web app pentesting, network pentesting, reporting |
| **Key Tools** | Burp Suite, Nmap, Metasploit, Gobuster, ffuf |
| **Extra Skills** | Report writing, client communication, time management |
| **Top Certs** | eJPT → PNPT → OSCP |
| **Salary Range** | $70K-$130K (junior to senior) |
| **Best For** | People who enjoy breaking things, variety, and problem-solving |

### 2. Red Team Operator

| Aspect | Details |
|--------|---------|
| **Core Skills** | AD attacks, C2 infrastructure, evasion, social engineering |
| **Key Tools** | Cobalt Strike/Sliver, NPS/SharpHound, Mimikatz |
| **Extra Skills** | PowerShell/C#/Nim coding, OPSEC, physical security |
| **Top Certs** | OSCP → CRTO → OSEP |
| **Salary Range** | $100K-$180K |
| **Best For** | People who love stealth, creativity, and advanced technical challenges |

### 3. Blue Team Analyst

| Aspect | Details |
|--------|---------|
| **Core Skills** | SIEM, log analysis, detection, incident response |
| **Key Tools** | Splunk, Wazuh, ELK, Velociraptor, TheHive |
| **Extra Skills** | Scripting (Python/PowerShell), threat intelligence, communication |
| **Top Certs** | BTL1 → CySA+ → CISSP |
| **Salary Range** | $60K-$120K |
| **Best For** | People who enjoy defense, patterns, and systematic analysis |

### 4. SOC Analyst

| Aspect | Details |
|--------|---------|
| **Core Skills** | Alert triage, escalation, basic investigation |
| **Key Tools** | SIEM dashboards, ticketing systems, EDR |
| **Extra Skills** | Shift work, stress management, communication |
| **Top Certs** | Security+ → CySA+ → BTL1 |
| **Salary Range** | $50K-$90K |
| **Best For** | Entry point into cybersecurity, structured work |

### 5. Incident Responder

| Aspect | Details |
|--------|---------|
| **Core Skills** | Forensic analysis, containment, eradication, recovery |
| **Key Tools** | Volatility, Autopsy, FTK Imager, Velociraptor |
| **Extra Skills** | Cool under pressure, excellent documentation, business communication |
| **Top Certs** | BTL1 → GCFE/GCFA → CISSP |
| **Salary Range** | $80K-$150K |
| **Best For** | Crisis-handlers, investigators, puzzle solvers |

### 6. Malware Analyst

| Aspect | Details |
|--------|---------|
| **Core Skills** | Reverse engineering, disassembly, debugging, YARA |
| **Key Tools** | Ghidra, IDA Pro, x64dbg, procmon |
| **Extra Skills** | Assembly (x86/x64), C/C++, PE structure |
| **Top Certs** | Practical malware analysis certs, GREM |
| **Salary Range** | $90K-$160K |
| **Best For** | People who love deep technical analysis, disassembly, puzzles |

### 7. Digital Forensics Expert

| Aspect | Details |
|--------|---------|
| **Core Skills** | Disk/memory forensics, chain of custody, court testimony |
| **Key Tools** | Autopsy, FTK, Volatility, EnCase |
| **Extra Skills** | Legal knowledge, report writing for court, procedure |
| **Top Certs** | GCFE → GCFA → EnCE |
| **Salary Range** | $70K-$140K |
| **Best For** | Methodical, detail-oriented, procedure-followers |

### 8. Security Engineer

| Aspect | Details |
|--------|---------|
| **Core Skills** | Architecture, configuration, automation, tool deployment |
| **Key Tools** | Firewalls, EDR, SIEM, Cloud, IAM |
| **Extra Skills** | Scripting, infrastructure knowledge, wide tool knowledge |
| **Top Certs** | Security+ → CISSP → CCSP |
| **Salary Range** | $90K-$160K |
| **Best For** | Builders, implementors, people who love configuring security solutions |

### 9. Cloud Security Engineer

| Aspect | Details |
|--------|---------|
| **Core Skills** | AWS/Azure/GCP security, IAM, cloud architecture |
| **Key Tools** | Terraform, CloudTrail, GuardDuty, Security Hub |
| **Extra Skills** | IaC (Terraform/CloudFormation), container security, DevSecOps |
| **Top Certs** | AWS Security Specialty → CCSP → CISSP |
| **Salary Range** | $110K-$180K |
| **Best For** | Cloud-native enthusiasts, architects, automation lovers |

### 10. DevSecOps Engineer

| Aspect | Details |
|--------|---------|
| **Core Skills** | CI/CD security, SAST/DAST, container security, IaC |
| **Key Tools** | Jenkins/GitHub Actions, Trivy, SonarQube, Checkov |
| **Extra Skills** | Programming (Python/Go), Docker/K8s, pipeline management |
| **Top Certs** | AWS Security Specialty → CSSLP |
| **Salary Range** | $100K-$170K |
| **Best For** | Developers who shift to security, automation-first mindset |

### 11. Security Researcher

| Aspect | Details |
|--------|---------|
| **Core Skills** | Vulnerability discovery, exploit development, publication |
| **Key Tools** | Fuzzers, debuggers, disassemblers, PoC development |
| **Extra Skills** | Academic writing, presentation skills, deep C/Assembly |
| **Top Certs** | OSCP → OSED → OSWE |
| **Salary Range** | $80K-$200K+ |
| **Best For** | Academic-minded, deep-divers, people who love finding 0-days |

### 12. Bug Bounty Hunter

| Aspect | Details |
|--------|---------|
| **Core Skills** | Recon automation, web security, reporting |
| **Key Tools** | Burp Suite, nuclei, subfinder, ffuf |
| **Extra Skills** | Self-discipline, writing skills, patience, persistence |
| **Top Certs** | Not needed (results speak) |
| **Salary Range** | $0-$500K+ (highly variable) |
| **Best For** | Independent workers, self-starters, people who love variety |

---

## 12-Month Learning Plan

### Month 1-2: Foundations 🔶

```
Week 1-2:   Computer Fundamentals + CS50
Week 3-4:   Linux Basics (Linux Journey + Bandit)
Week 5-6:   Networking Basics (Cisco skills + Wireshark)
Week 7-8:   Windows Fundamentals + PowerShell
```

- [ ] Harvard CS50
- [ ] Complete OverTheWire Bandit (levels 0-34)
- [ ] Complete Cisco Networking Basics
- [ ] Setup home lab with 3 VMs
- [ ] Start Google Cybersecurity Certificate (audit)

### Month 3-4: Programming & Cyber Fundamentals 🔶

```
Week 9-10:  Python for cybersecurity
Week 11-12: Bash & PowerShell scripting
Week 13-14: Cybersecurity Fundamentals (CIA, risk, etc.)
Week 15-16: Cryptography basics
```

- [ ] Complete Google Cybersecurity Certificate
- [ ] Write 5 Python security tools (scanner, hasher, etc.)
- [ ] Pass ISC2 Certified in Cybersecurity (free)
- [ ] Complete Cryptohack (first 20 challenges)

### Month 5-6: Web Security 🔶

```
Week 17-18: HTTP, APIs, OWASP Top 10
Week 19-20: Burp Suite + SQL injection
Week 21-22: XSS, CSRF, SSRF, File Upload
Week 23-24: JWT, OAuth, CORS
```

- [ ] Complete all PortSwigger SQL injection labs
- [ ] Complete all PortSwigger XSS labs
- [ ] Complete OWASP Juice Shop (50%+ flags)
- [ ] Pass CompTIA Security+

### Month 7-8: Ethical Hacking 🔶

```
Week 25-26: Pentesting methodology + Recon
Week 27-28: Exploitation with Metasploit + manual
Week 29-30: Linux & Windows privesc
Week 31-32: Active Directory attacks
```

- [ ] Complete TCM's Practical Ethical Hacking course
- [ ] Hack 10+ HTB Starting Point/VulnHub machines
- [ ] Complete TJ_Null's list (at least 20 machines)
- [ ] Pass eJPT certification

### Month 9-10: Focus & Depth 🔶

```
Week 33-34: Digital Forensics
Week 35-36: SIEM + SOC (Wazuh setup)
Week 37-38: Containers + Cloud security
Week 39-40: Pass PNPT or BTL1
```

- [ ] Complete TryHackMe Digital Forensics path
- [ ] Set up Wazuh at home
- [ ] Complete Flaws.cloud challenges
- [ ] Pass PNPT certification

### Month 11-12: Portfolio & Job Prep 🔶

```
Week 41-42: Build portfolio projects
Week 43-44: Write blog posts + publish reports
Week 45-46: Interview preparation
Week 47-48: Apply & network
```

- [ ] 3 strong GitHub projects
- [ ] 5+ blog posts/writeups
- [ ] LinkedIn profile optimized
- [ ] Resume + portfolio ready
- [ ] Apply to 20+ jobs/week

---

## 24-Month Mastery Roadmap

### Year 1 (Months 1-12)
```
✅ Google Cybersecurity Certificate
✅ OverTheWire Bandit (levels 0-34)
✅ PortSwigger Web Security Academy (all labs)
✅ Cryptohack (20+ challenges)
✅ Wireshark mastery
✅ OSWP/PortSwigger all labs
✅ 25+ VulnHub/HTB machines
✅ eJPT certification
✅ PNPT certification OR BTL1 (choose track)
✅ Home lab with 5+ VMs
✅ 5+ blog posts
✅ 3+ GitHub projects
```

### Year 2 (Months 13-24)

| Quarter | Focus | Milestones |
|---------|-------|------------|
| **Q1** (Months 13-15) | OSCP Preparation | 50+ HTB/VulnHub machines, PWK course, OSCP exam |
| **Q2** (Months 16-18) | Specialization | Choose track (Red/Blue/Cloud/Malware), deep dive, advanced cert |
| **Q3** (Months 19-21) | Professional Growth | Blog consistently, speak at meetups, contribute to open source |
| **Q4** (Months 22-24) | Senior Role Prep | CISSP preparation, leadership skills, mentor others |

### Year 2 Milestones
- [ ] OSCP Certified (Gold standard achieved)
- [ ] Specialized cert (CRTO/OSED/OSWE/Azure Security/GCFE)
- [ ] 100+ total machines hacked
- [ ] 1 CVE found (optional but impressive)
- [ ] Spoken at a meetup or conference
- [ ] Published 10+ technical blog posts
- [ ] Contributed to open-source security tools
- [ ] Mentored 1-2 beginners
- [ ] CISSP (if aiming for senior/management)

---

## Portfolio Checklist

### Essential Portfolio Items

- [ ] **Personal Security Blog** (Medium, Dev.to, or your own site)

  *Write about:*
  - HTB/VulnHub machine walkthroughs
  - Bug bounty writeups
  - Tool tutorials
  - Security concepts explained simply

- [ ] **GitHub Profile** (make it look professional)

  *Must have:*
  - Profile README with security badges
  - Pinned repos of your best projects
  - Clean code with documentation
  - Well-written README for each project

- [ ] **LinkedIn Profile** (optimized for recruiters)

  *Must have:*
  - Professional headshot
  - Banner showing your focus area
  - Detailed experience section
  - Recommendations
  - Certifications listed
  - Security-related posts (at least 1x/week)

### Portfolio Projects

| Project | Description | Showcases |
|---------|-------------|-----------|
| Port Scanner | Multi-threaded TCP scanner in Python | Python, networking |
| Hash Cracker | Multi-algorithm cracker with rules | Cryptography, optimization |
| Automated Recon Pipeline | Subdomain discovery → scanning | Automation, web security |
| SIEM Homelab | Wazuh/ELK with custom alerts | Blue team, detection |
| AD Attack Lab | Full attack chain from zero to DA | Red team, AD |
| Forensic Analysis Report | Real case analysis walkthrough | Forensics, reporting |
| Custom Malware Analysis | Sample analysis with YARA rules | Malware analysis |

### Video Portfolio (Optional but Powerful)

- Record 5-10 minute walkthroughs of your projects
- Upload to YouTube/LinkedIn
- Show methodology, not just results

---

## GitHub Project Roadmap

### Beginner Projects (Months 1-3)

```
├── python-port-scanner/
│   ├── scanner.py
│   ├── README.md
│   └── requirements.txt
├── hash-cracker/
│   ├── cracker.py
│   ├── wordlists/
│   └── README.md
├── linux-hardening-script/
│   ├── harden.sh
│   ├── README.md
│   └── test.sh
└── network-analyzer/
    ├── analyze.py
    ├── README.md
    └── examples/
```

### Intermediate Projects (Months 4-8)

```
├── web-recon-toolkit/
│   ├── recon.py
│   ├── subdomain_enum.py
│   ├── dir_fuzz.py
│   ├── screenshots.py
│   └── README.md
├── AD-Lab-Setup/
│   ├── ansible/
│   ├── scripts/
│   ├── README.md
│   └── diagram.png
├── automated-pentest-framework/
│   ├── modules/
│   ├── reports/
│   ├── main.py
│   └── README.md
├── forensics-toolkit/
│   ├── memory_analyzer.py
│   ├── disk_analyzer.py
│   ├── log_parser.py
│   └── README.md
└── siem-homelab/
    ├── wazuh-config/
    ├── custom-rules/
    ├── dashboards/
    └── README.md
```

### Advanced Projects (Months 9-24)

```
├── custom-c2-implant/       (Python/Nim/Rust)
│   ├── server/
│   ├── implant/
│   ├── modules/
│   ├── README.md
│   └── demo.gif
├── malware-analysis-reports/
│   ├── sample_001/
│   ├── sample_002/
│   ├── yara-rules/
│   └── README.md
├── cloud-security-scanner/
│   ├── aws_scanner.py
│   ├── azure_scanner.py
│   ├── reports/
│   └── README.md
├── detection-engineering/
│   ├── sigma-rules/
│   ├── snort-rules/
│   ├── yara-rules/
│   └── README.md
└── bug-bounty-recon-pipeline/
    ├── auto_recon.sh
    ├── notification.py
    ├── report_template.md
    ├── wordlists/
    └── README.md
```

---

## Interview Preparation Roadmap

### Knowledge Areas

| Area | Key Topics |
|------|------------|
| **Networking** | OSI model, TCP/IP, DNS, HTTP, subnetting, common ports |
| **Operating Systems** | Linux filesystem, Windows AD, permissions, processes |
| **Security Concepts** | CIA, AAA, risk management, defense in depth, Zero Trust |
| **Web Security** | OWASP Top 10, Burp Suite, web attacks |
| **Cryptography** | Symmetric vs asymmetric, hashing, PKI, TLS |
| **Tools** | Nmap, Wireshark, Metasploit, Burp Suite, Ghidra |
| **Methodology** | Pentesting phases, incident response lifecycle, forensics process |

### Common Interview Questions

**Technical**:
1. Walk me through how you'd penetration test a web application.
2. Explain the difference between symmetric and asymmetric encryption.
3. How does a TCP three-way handshake work?
4. What's the difference between IDS and IPS?
5. How would you escalate privileges on a Linux system?
6. Explain how you'd set up a home lab.
7. What's in the OWASP Top 10?
8. How does SSL/TLS work?
9. What is the difference between a vulnerability assessment and a penetration test?
10. Explain how you'd respond to a ransomware incident.

**Behavioral** (STAR Method):
1. Tell me about a time you solved a difficult technical problem.
2. Describe a situation where you had to work under pressure.
3. How do you stay current with security threats?
4. Tell me about a time you made a mistake and how you handled it.
5. Describe a project you're proud of.

**Scenario-Based**:
1. You find a critical vulnerability. What do you do?
2. An alert comes in at 3 AM for potential data exfiltration. Walk me through your response.
3. Your client wants you to test beyond scope. How do you handle it?

### Interview Prep Schedule

| Week | Focus |
|------|-------|
| 1-2 | Review all fundamentals (Networking, OS, Security concepts) |
| 3-4 | Practice technical questions (record yourself) |
| 5 | Behavioral questions with STAR method |
| 6 | Mock interviews (with peers or paid services) |
| 7 | Whiteboarding practice (explain concepts without tools) |
| 8 | Final review + applications |

---

## Communities & Discord Servers

### Top Free Cybersecurity Communities

| Community | Link | Best For | Free? |
|-----------|------|----------|-------|
| **r/netsec** | [reddit.com/r/netsec](https://reddit.com/r/netsec) | Security news, discussions | ✅ |
| **r/cybersecurity** | [reddit.com/r/cybersecurity](https://reddit.com/r/cybersecurity) | Career advice, general | ✅ |
| **r/AskNetsec** | [reddit.com/r/AskNetsec](https://reddit.com/r/AskNetsec) | Questions, help | ✅ |
| **Hack The Box Forums** | [forum.hackthebox.com](https://forum.hackthebox.com) | CTF discussions, help | ✅ |
| **TryHackMe Discord** | [discord.gg/tryhackme](https://discord.gg/tryhackme) | Beginner learning, help | ✅ |
| **The Cyber Mentor Discord** | [discord.gg/thecybermentor](https://discord.gg/thecybermentor) | Pentesting, career | ✅ |
| **Infosec Prep Discord** | [discord.gg/infosecprep](https://discord.gg/infosecprep) | OSCP prep | ✅ |
| **BSides** (local chapters) | [bsides.org](https://bsides.org) | Local meetups, networking | ✅ |
| **Women in CyberSecurity (WiCyS)** | [wicys.org](https://www.wicys.org) | Women in security | ✅ |
| **OWASP Chapter** | [owasp.org/chapters](https://owasp.org/chapters) | AppSec meetups, local | ✅ |
| **Defcon Groups** (local) | [defcongroups.org](https://defcongroups.org) | Local hacking meetups | ✅ |
| **SANS DFIR Discord** | [discord.gg/sans](https://discord.gg/sans) | DFIR discussions | ✅ |

### Discord Servers You Should Join

1. **[TryHackMe](https://discord.gg/tryhackme)** — Best for beginners, tons of help channels
2. **[The Cyber Mentor](https://discord.gg/thecybermentor)** — Great for pentesting, job advice
3. **[Hack The Box](https://discord.gg/hackthebox)** — For intermediate/advanced hacking
4. **[InfoSec Prep](https://discord.gg/infosecprep)** — OSCP community
5. **[CyberSec People](https://discord.gg/cybersecpeople)** — General cybersecurity community

---

## Common Beginner Mistakes & How to Avoid Them

### 🚫 Mistake 1: Stuck in "Tutorial Hell"

**The Problem**: Watching endless tutorials without ever practicing.

**Fix**: Follow the 70/30 rule → 30% learning, 70% doing. After each tutorial, immediately do something with what you learned. Close the video and try to replicate it from memory.

### 🚫 Mistake 2: Trying to Learn Everything at Once

**The Problem**: Jumping between networking, Python, AD, cloud, forensics without depth.

**Fix**: Focus on ONE path. Master the fundamentals (Linux + Networking + 1 language) before branching out. Use the "S" curve — go deep, then wide.

### 🚫 Mistake 3: Not Building a Home Lab

**The Problem**: Only using browser-based labs, never setting up your own environment.

**Fix**: Day 1, set up VMs. Day 2, network them. Day 3, start breaking things. A home lab is the single most important investment you'll make.

### 🚫 Mistake 4: Avoiding the Command Line

**The Problem**: Using GUIs for everything, being afraid of the terminal.

**Fix**: Force yourself to use the terminal exclusively for 30 days. No file explorer, no GUI tools. You'll thank yourself later.

### 🚫 Mistake 5: Not Documenting or Note-Taking

**The Problem**: Learning something and forgetting it a week later.

**Fix**: Use Obsidian. Every single day, write at least one note. Create your own knowledge base. Revisit and update notes regularly.

### 🚫 Mistake 6: Doing Unethical Things

**The Problem**: Scanning/hacking without permission. This is a crime.

**Fix**: ONLY hack systems you own or have explicit written permission to test. Use platforms like TryHackMe, HTB, VulnHub, or your own lab.

### 🚫 Mistake 7: Neglecting Soft Skills

**The Problem**: Thinking technical skills are all that matters.

**Fix**: Practice writing, speaking, and presenting. Security is a people business. Most security professionals spend 50%+ of their time communicating.

### 🚫 Mistake 8: Not Building a Portfolio Early

**The Problem**: Waiting until you're "good enough" to start a portfolio.

**Fix**: Start your blog and GitHub TODAY. Even if it's just notes and a simple Python script. Recruiters want to see progress, not perfection.

### 🚫 Mistake 9: Ignoring the Blue Side

**The Problem**: Only wanting to hack, ignoring defense.

**Fix**: Learn defense alongside offense. The best attackers understand defense deeply. Understanding SIEM, detection, and forensics makes you a much better pentester.

### 🚫 Mistake 10: Comparing Yourself to Others

**The Problem**: Seeing people on Twitter/LinkedIn with 10+ years of experience and feeling behind.

**Fix**: Your only competition is yesterday's you. This industry is massive and always needs more people. Focus on your journey, not anyone else's.

---

## Tips for Building a Strong Cybersecurity Portfolio That Attracts Recruiters

### 1. Show, Don't Tell

Bad: "I know penetration testing"
Good: A GitHub repo with a full pentest report on a VulnHub machine

Bad: "I know Python"
Good: A Python port scanner with 500+ stars

### 2. Quality Over Quantity

- 3 amazing projects > 20 mediocre ones
- Each project should have:
  - Clean, well-commented code
  - A professional README
  - Screenshots or GIFs of it working
  - Installation instructions
  - Example usage

### 3. Write Technical Blog Posts

Blogging proves you can:
- Explain complex concepts clearly
- Document your work
- Teach others (a highly valued skill)
- Think critically

**Content ideas**:
- "How I hacked VulnHub machine X — Full Walkthrough"
- "Building a Port Scanner in Python — Step by Step"
- "My Journey Through the OWASP Juice Shop"
- "Setting Up a Home SIEM with Wazuh"
- "Understanding Active Directory Attacks: From Zero to Domain Admin"

### 4. Get Active on LinkedIn

- Post at least 3x/week
- Share your learning journey
- Comment on other people's posts
- Connect with recruiters and professionals
- Share achievements (certifications, machines, projects)

### 5. Contribute to Open Source

- Fix documentation in security tools
- Add a feature to an open-source tool
- Submit YARA rules to public repositories
- Contribute Sigma rules

### 6. Create a Professional Resume

- One page (two max)
- Quantify achievements ("Scanned 1000+ hosts", "Identified 50+ vulnerabilities")
- Tailor to each role
- Include a link to your portfolio
- List relevant certifications

### 7. Network Authentically

- Attend local meetups (BSides, OWASP, Defcon groups)
- Join Discord communities and help others
- Follow up with people you meet
- Be helpful, not transactional

### 8. Get Real Experience (Even Without a Job)

- Volunteer pentesting for non-profits (with written permission!)
- Contribute to bug bounty VDP programs
- Offer to help small businesses with security assessments
- Create security content (YouTube, blog, courses)

---

## 🏆 Final Words of Wisdom

> **"Security is a journey, not a destination. There is no 'arriving' — only constant learning."**

**The most important skills you can develop:**
1. **Curiosity** — Never stop asking "why" and "how"
2. **Persistence** — You will fail. A lot. Keep going.
3. **Humility** — You don't know everything. No one does.
4. **Ethics** — Your skills can help or harm. Choose wisely.
5. **Generosity** — Share what you learn. Teach others.

**Your roadmap to success:**
```
Learn → Practice → Fail → Learn from failure → Practice more → Succeed → Teach → Repeat
```

**Remember**: Every expert was once a beginner who never gave up.

---

*This roadmap was created to be your companion, not your dictator. Adapt it to your pace, interests, and circumstances. The only rule is: don't stop learning.*

**Now go build your lab. The world needs more good hackers.** 🛡️

---

> **📌 Want to contribute or update this roadmap?**
> This is a living document. Resources go outdated, new tools emerge, and attack techniques evolve.
> Keep learning, stay curious, and share what you find.
